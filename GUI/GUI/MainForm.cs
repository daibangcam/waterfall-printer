using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Diagnostics;
using System.IO;
using System.IO.Ports;
using System.Xml;
using Excel = Microsoft.Office.Interop.Excel;
using System.Xml.Serialization;
using System.Collections;

using InterfaceDef;
using IScriptConfDef;

namespace BKWGen3
{
    public partial class MainForm : Form, ICommSetting, IScriptConf
    {

        public byte[,] WarArray;
        public byte[,] GrValue;
        public string ImageFileName;
        private IScriptConfDef.UScriptParams conf;

        public MainForm()
        {
            InitializeComponent();
        }

        #region Implement the interface ICommSetting
        private Comm port;
        public Comm Port
        {
            set { this.port = value; }
            get { return this.port; }
        }
        #endregion

        #region Implement the interface IScript
        public UScriptParams usc
        {
            set
            {
                conf.repeat = value.repeat;
                conf.dlbefore = value.dlbefore;
                conf.dlrepeat = value.dlrepeat;
                conf.dlafter = value.dlafter;
                conf.align = value.align;
            }

            get
            {
                return conf;
            }
        }
        #endregion

        private void butOpen_Click(object sender, EventArgs e)
        {
            OpenImage();
            GrGen(GrValue);
            GrPrint(WarArray);
        }

        private void OpenImage()
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (ImagesFolderName != "C:\\Users\\daiba\\OneDrive - Ho Chi Minh city University of Food Industry\\Desktop\\Script\\Images")
            {
                openFileDialog.InitialDirectory = ImagesFolderName;
            }
            openFileDialog.Filter = "Image Files(*.BMP;*.JPG;*.GIF;*.PNG*)|*.BMP;*.JPG;*.GIF;*.PNG|All files (*.*)|*.*";
            if (openFileDialog.ShowDialog(this) == DialogResult.OK)
            {
                LoadImage(openFileDialog.FileName);
            }  
        }

        private void LoadImage(string img_fn)
        {
            if (File.Exists(img_fn))
            {
                Image img = Image.FromFile(img_fn);
                txtImageFileName.Text = img_fn;
                ImageFileName = txtImageFileName.Text;
                picBox.Image = img;
                GrConv(img, (double)numWidth.Value, (double)numHeight.Value, true);
                /*
                lblDir.Text = "Import Success!";
                lblDir.ForeColor = Color.Blue;
                 */ 
            }
            else
            {
                /*
                lblDir.Text = "Import Fail!";
                lblDir.ForeColor = Color.Yellow;
                 */ 
            }
        }

        //const double dw = 11; // milimet
        //const double dh = 20; // milimet
        const double dw = 15; // milimet
        const double dh = 20; // milimet
        int GridWidth;
        int GridHeight;

        private void MainForm_Load(object sender, EventArgs e)
        {
            GridWidth = pnGrid.Width;
            GridHeight = pnGrid.Height;
        }

        /*
         * Function GrConv exports the image to the array
         * img: Input image to convert to array
         * w:   Width of the screen display (mm)
         * h:   Height of the screen display (mm)
         */
        private void GrConv(Image img, double w, double h, bool visible)
        {
            // Calculate a number of cells along width and height direction
            int lw = (int)(w / dw);
            int lh = (int)(h / dh);

            // Init the grid cell values
            GrValue = new byte[lh, lw];

            // Panel Grid resize, dimensions
            pnGrid.Width = GridWidth; // default size
            pnGrid.Height = GridHeight;
            double ly = (double)pnGrid.Height;
            double tmp = (double)pnGrid.Width * h / w;
            if (ly > tmp) ly = tmp;
            double lx = ly * w / h;
            int dx = (int)lx / lw;
            int dy = (int)ly / lh;
            pnGrid.Width = dx * lw;
            pnGrid.Height = dy * lh;

            pnGrid.Location = new Point((GridWidth - pnGrid.Width) / 2, pnGrid.Location.Y);

            // Resize an image to the size of screen
            Bitmap imgResize = new Bitmap(pnGrid.Width, pnGrid.Height);
            Graphics g = Graphics.FromImage((Image)imgResize);
            g.DrawImage(img, 0, 0, pnGrid.Width, pnGrid.Height);

            // Calculate a number of pixels in each computed cell
            Bitmap bm = new Bitmap(imgResize);
            int bm_dw = bm.Width / lw;
            int bm_dh = bm.Height / lh;

            // Load an image
            if (ckbLoadImg.Checked)
            {
                pnGrid.BackgroundImage = imgResize;
            }
            else
            {
                pnGrid.BackgroundImage = null;
            }
            pnGrid.Refresh();

            System.Drawing.Pen penGray, penRed;
            penGray = new System.Drawing.Pen(System.Drawing.Color.Green, 1);
            penRed = new System.Drawing.Pen(System.Drawing.Color.Red, 3);
            System.Drawing.Graphics formGraphics = this.pnGrid.CreateGraphics();
            if (visible)
            {
                // Draw grid
                for (int i = 0; i < lw + 1; i++)
                {
                    formGraphics.DrawLine(penGray, i * dx, 0, i * dx, lh * dy);
                }
                for (int j = 0; j < lh + 1; j++)
                {
                    formGraphics.DrawLine(penGray, 0, j * dy, lw * dx, j * dy);
                }
            }

            int flag = (ckbNegative.Checked) ? 1 : 0;

            bool b = ckbReverseImage.Checked;
            // Scan cells along x-axis
            for (int i = 0; i < lw; i++)
            {
                // Scan cells along y-axis
                for (int j = 0; j < lh; j++)
                {
                    int px = 0;
                    int n = 0;
                    // Scan pixels in cell(i,j) along x-axis
                    for (int k = 0; k < bm_dw; k++)
                    {
                        // Scan pixels in cell(i,j) along y-axis
                        for (int l = 0; l < bm_dh; l++)
                        {
                            Color c = bm.GetPixel((int)(i * bm_dw) + k, (int)(j * bm_dh) + l);
                            int t = (int)(0.2126 * c.R + 0.7152 * c.G + 0.0722 * c.B);
                            //int t = (int)(c.R + c.G +c.B)/3;
                            if (t < slider.Value) t = 0 + 255 * flag;
                            else t = 255 - 255 * flag;
                            px += t;
                            n += 1;
                        }
                    }
                    px /= n;
                    float x0 = i * dx +0.5f * dx;
                    float y0 = j * dy;
                    float y1 = (j + 1) * dy;
                    GrValue[j, i] = 0;
                    if (px < 125)
                    {
                        GrValue[j, i] = 1;
                        if (visible)
                        {
                            formGraphics.DrawLine(penRed, x0, y0, x0, y1);
                        }
                    }
                }
            }

            penGray.Dispose();
            penRed.Dispose();
            formGraphics.Dispose();
        }

        private void GrConv1(Image img, double w, double h, bool visible)
        {
            // Calculate a number of cells along width and height direction
            int lw = (int)(w / dw);
            int lh = (int)(h / dh);

            // Init the grid cell values
            GrValue = new byte[lh, lw];

            // Panel Grid resize, dimensions
            pnGrid.Width = 684; // default size
            pnGrid.Height = 667;
            double ly = (double)pnGrid.Height;
            double tmp = (double)pnGrid.Width * h / w;
            if (ly > tmp) ly = tmp;
            double lx = ly * w / h;
            int dx = (int)lx / lw;
            int dy = (int)ly / lh;
            pnGrid.Width = dx * lw;
            pnGrid.Height = dy * lh;

            // Resize an image to the size of screen
            Bitmap imgResize = new Bitmap(pnGrid.Width, pnGrid.Height);
            Graphics g = Graphics.FromImage((Image)imgResize);
            g.DrawImage(img, 0, 0, pnGrid.Width, pnGrid.Height);

            // Calculate a number of pixels in each computed cell
            Bitmap bm = new Bitmap(imgResize);
            int bm_dw = bm.Width / lw;
            int bm_dh = bm.Height / lh;

            // Load an image
            if (ckbLoadImg.Checked)
            {
                pnGrid.BackgroundImage = imgResize;
            }
            else
            {
                pnGrid.BackgroundImage = null;
            }
            pnGrid.Refresh();

            System.Drawing.Pen penGray, penRed;
            penGray = new System.Drawing.Pen(System.Drawing.Color.Green, 1);
            penRed = new System.Drawing.Pen(System.Drawing.Color.Red, 3);
            System.Drawing.Graphics formGraphics = this.pnGrid.CreateGraphics();
            if (visible)
            {
                // Draw grid
                for (int i = 0; i < lw + 1; i++)
                {
                    formGraphics.DrawLine(penGray, i * dx, 0, i * dx, lh * dy);
                }
                for (int j = 0; j < lh + 1; j++)
                {
                    formGraphics.DrawLine(penGray, 0, j * dy, lw * dx, j * dy);
                }
            }

            int flag = (ckbNegative.Checked) ? 1 : 0;

            bool b = ckbReverseImage.Checked;
            // Scan cells along x-axis
            for (int i = 0; i < lw; i++)
            {
                // Scan cells along y-axis
                for (int j = 0; j < lh; j++)
                {
                    int px = 0;
                    int n = 0;
                    // Scan pixels in cell(i,j) along x-axis
                    for (int k = 0; k < bm_dw; k++)
                    {
                        // Scan pixels in cell(i,j) along y-axis
                        for (int l = 0; l < bm_dh; l++)
                        {
                            Color c = bm.GetPixel((int)(i * bm_dw) + k, (int)(j * bm_dh) + l);
                            int t = (int)(0.2126 * c.R + 0.7152 * c.G + 0.0722 * c.B);
                            //int t = (int)(c.R + c.G +c.B)/3;
                            if (t < slider.Value) t = 0 + 255 * flag;
                            else t = 255 - 255 * flag;
                            px += t;
                            n += 1;
                        }
                    }
                    px /= n;
                    float x0 = i * dx + 0.5f * dx;
                    float y0 = j * dy;
                    float y1 = (j + 1) * dy;
                    GrValue[j, i] = 0;
                    if (px < 125)
                    {
                        GrValue[j, i] = 1;
                        if (visible)
                        {
                            formGraphics.DrawLine(penRed, x0, y0, x0, y1);
                        }
                    }
                }
            }

            penGray.Dispose();
            penRed.Dispose();
            formGraphics.Dispose();
        }

        
        public void GrGen(byte[,] val)
        {
            int row = val.GetLength(0);
            int col = val.GetLength(1);

            uint n = (uint)col;
            if ((n % 8) == 0) n = n / 8;
            else n = n / 8 + 1;

            WarArray = new byte[row, n];
            int l = 0;

            bool b = ckbReverseImage.Checked;
            for (int i = 0; i < row; i++)
            {
                l = 0;
                for (int j = 0; j < n; j++)
                {
                    byte c = 0x00;
                    for (byte k = 0; ((k < 8) && ((8 * j + k) < col)); k++)
                    {
                        if (b)
                        {
                            if (val[row - 1 - i, col - 1 - 8 * j - k] == 1) // row in reverse order, col in reverse order
                            {
                                c |= (byte)(0x01 << (7 - k));
                            }
                        }
                        else
                        {
                            if (val[row - 1 - i, 8 * j + k] == 1) // row in reverse order
                            {
                                c |= (byte)(0x01 << (7 - k));
                            }
                        }
                    }
                    WarArray[i, l] = c;                    
                    l++;
                }
            }            
        }

        /*
         * Because maximum size of "uint8_t" array type inside MCU is 255 
         * So that any array, its size is greater than 255, must be divide to smaller ones
         * We choose 250 bytes on each array
         */
        /*
        const int MAX_SIZE = 250;
        public void GrPrint(byte[,] arr)
        {
            int row = arr.GetLength(0); // number of rows
            int n = arr.GetLength(1);  // number of columns

            int div = row / MAX_SIZE;
            rtxtGen.Text = ""; // clear text box
            int i, j, k = 0;
            string strArr;
            do
            {
                strArr = "";
                for (i = 0; ((i < row) && (i < MAX_SIZE)); i++)
                {
                    strArr += "\n   ";
                    for (j = 0; j < n; j++)
                    {
                        string tmp = Convert.ToString(WarArray[k * MAX_SIZE + i, j], 10).PadLeft(3, ' ');
                        strArr += tmp + ", ";
                    }
                }
                strArr = string.Format("uint8_t c_{2}[{0}][{1}] = {{", i, n, k++) + strArr + "\n};\n";
                rtxtGen.Text += strArr; // print to rich text box
                row -= MAX_SIZE;

            } while (row > 0);

            //rtxtGen.SelectAll();
            //rtxtGen.Copy();
        }
        */

        public void GrPrint(byte[,] arr)
        {
            int row = arr.GetLength(0); // number of rows
            int n = arr.GetLength(1);  // number of columns

            rtxtGen.Text = ""; // clear text box
            int i, j;

            UInt16 total = (UInt16)(row * n + 4);
            byte[] tmp1 = new byte[2];
            byte[] tmp2 = new byte[2];
            ConvertUint16ToBytes(total, tmp1, 0);
            ConvertUint16ToBytes((UInt16)n, tmp2, 0);

            string var_name = string.Format("uint8_t c[{0}]", total);
            string strArr = string.Format("{0} = {{ {1}, {2}, {3}, {4},", var_name, tmp1[0], tmp1[1], tmp2[0], tmp2[1]);

            for (i = 0; i < row; i++)
            {
                strArr += '\n';
                for (j = 0; j < n; j++)
                {
                    string tmp = Convert.ToString(WarArray[i, j], 10).PadLeft(3, ' ');
                    strArr += tmp + ", ";
                }
            }

            strArr += "\n};";
            rtxtGen.Text += strArr; // print to rich text box

            rtxtGen.SelectAll();
            rtxtGen.Copy();
        }

        private void slider_Scroll(object sender, EventArgs e)
        {
            lblSlider.Text = slider.Value.ToString();
        }

        private void butGen_Click(object sender, EventArgs e)
        {
            if (ConfigParamIsChanged)
            {
                // Reload image
                LoadImage(txtImageFileName.Text);
            //    ConfigParamsUnchange();
            }
            GrGen(GrValue);
            GrPrint(WarArray);
        }

        public string TableFileName;
        public string WorkFolderName;
        public string ImagesFolderName;
        public string TableRange = "[Gen$B4:E92]";
        public object[] BKW_Table;
        public int BKW_TableRow;
        public int BKW_TableCol;
        public object[] BKW_GenTable;
        public int BKW_GenTableRow;
        public int BKW_GenTableCol;

        private void butOpenXls_Click(object sender, EventArgs e)
        {
            // Open xls file
            OpenFileDialog openFileDialog = new OpenFileDialog();
            //openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            if (Directory.Exists(WorkFolderName))
            {
                TableFileName = WorkFolderName + "\\BKWTable.xlsm";
                // Load table to grid view
                try
                {
                    System.Data.OleDb.OleDbConnection MyConnection;
                    System.Data.DataSet ds;
                    System.Data.OleDb.OleDbDataAdapter MyCommand;
                    MyConnection = new System.Data.OleDb.OleDbConnection("provider=Microsoft.ACE.OLEDB.12.0;Data Source='" + TableFileName + "';Extended Properties=Excel 12.0 Xml;");
                    MyCommand = new System.Data.OleDb.OleDbDataAdapter("select * from " + TableRange, MyConnection);
                    ds = new System.Data.DataSet();
                    MyCommand.Fill(ds);
                    dataView.DataSource = ds.Tables[0];

                    // Creat object hold on data
                    BKW_TableRow = dataView.Rows.Count;
                    BKW_TableCol = dataView.Columns.Count;
                    BKW_Table = new object[BKW_TableRow];
                    for (int row = 0; row < BKW_TableRow; row++)
                    {
                        object[] arr = new object[BKW_TableCol];
                        for (int col = 0; col < BKW_TableCol; col++)
                        {
                            if (dataView.Rows[row].Cells[col].Value != null)
                                arr[col] = dataView.Rows[row].Cells[col].Value;
                        }
                        BKW_Table[row] = arr;
                    }
                    dataView.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.ColumnHeader;
                    dataView.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllHeaders;
                    MyConnection.Close();

                    rtxtGen.Text = BKW_Table.ToString();
                    MessageBox.Show("Import Done!");
                    
                }

                catch (Exception ex)
                {
                    MessageBox.Show("Invalid table!");
                }
            }
            else
            {
                MessageBox.Show("PLease setting working directory first!");
            }
            TableGen();
        }

        private void TableGen()
        {
            if (BKW_TableRow == 0) return;
            BKW_GenTableRow = BKW_TableRow;
            BKW_GenTable = new object[BKW_GenTableRow]; //[addr][Name][gen_code]
            rtxtGen.Text = "START\n";
            for (int i = 0; i < BKW_GenTableRow; i++)
            {
                object[] arr =(object[])BKW_Table[i];
                object[] arrGen = new object[3];
                if ((arr[0] != null) && (arr[1] != null))
                {
                    try
                    {
                        arrGen[0] = arr[0]; //address
                        arrGen[1] = arr[1]; // name
                        double width = (double)arr[2];
                        double height = (double)arr[3];
                        rtxtGen.Text += (string)arrGen[1];
                        // Load image to process
                        string img_fn = ImagesFolderName + (string)arrGen[1] + ".bmp";
                        string tmp1 = ImagesFolderName + (string)arrGen[1] + ".png";
                        if (File.Exists(tmp1)) img_fn = tmp1;
                        if (File.Exists(img_fn))
                        {
                            Image img = Image.FromFile(img_fn);
                            picBox.Image = img;
                            GrConv(img, width, height, false);
                            WarArray = null;
                            GrGen(GrValue);
                            arrGen[2] = WarArray;
                            BKW_GenTable[i] = arrGen;
                            rtxtGen.Text += ": Success.\n";
                        }
                        else
                        {
                            rtxtGen.Text += ": Fail.\n";
                        }
                    }
                    catch
                    {
                        rtxtGen.Text += "Null variable!\n";
                    }
                }
                else
                {
                    rtxtGen.Text += "STOP\n";
                    break;
                }
            }
            TableWrite();
            
        }

        private void createNode( XmlTextWriter writer, int add, string name, string dat)
        {
            writer.WriteStartElement("Image");

            writer.WriteStartAttribute("address");
            writer.WriteString(add.ToString());
            writer.WriteEndAttribute();
            writer.WriteStartAttribute("name");
            writer.WriteString(name);
            writer.WriteEndAttribute();

            /*
            writer.WriteStartElement("Address");
            writer.WriteString(add.ToString());
            writer.WriteEndElement();
            writer.WriteStartElement("Name");
            writer.WriteString(name);
            writer.WriteEndElement();
            */

            //writer.WriteStartElement("Data");
            writer.WriteString(dat);
            //writer.WriteEndElement();
            writer.WriteEndElement();
        }

        public void TableWrite()
        {
            // Save to text file
            FileStream fs  = new FileStream(WorkFolderName + "\\table.c", FileMode.Create);
            FileStream fs1 = new FileStream(WorkFolderName + "\\table.h", FileMode.Create);
            StreamWriter sw  = new StreamWriter(fs);
            StreamWriter sw1 = new StreamWriter(fs1);

            // Export to xml file
            XmlTextWriter writer = new XmlTextWriter(WorkFolderName + "\\table.xml", System.Text.Encoding.UTF8);
            writer.WriteStartDocument(true);
            writer.Formatting = Formatting.Indented;
            writer.Indentation = 2;
            writer.WriteStartElement("Table");
            
            
            string src_head = @"
/*******************************************************************************
*
*  Project: BKWAR
* 
******************************************************************************/

/*******************************************************************************
*
*	Module			: table.c
*   Tool		  	: KeilC ARM 4.22a
*	Chip		  	: STM32F103C8
* 	History			: Begin Dec, 2013
*	Description	    : Application layer
*				
*	Author			: BKW AutoGen Tool		
*				
******************************************************************************/
#include ""table.h""; 

";

            string header_head = @"
/*******************************************************************************
*
*  Project: BKWAR
* 
******************************************************************************/

/*******************************************************************************
*
*	Module			: table.h
*   Tool		  	: KeilC ARM 4.22a
*	Chip		  	: STM32F103C8
* 	History			: Begin at Dec, 2013
*	Description	    : Application layer
*				
*	Author			: BKW AutoGen Tool		
*				
******************************************************************************/


";

            sw.WriteLine(src_head);
            sw1.WriteLine(header_head);

            for (int r = 0; r < BKW_GenTableRow; r++)
            {
                if (BKW_GenTable[r] != null)
                {
                    object[] tmp_arr = (object[])BKW_GenTable[r];
                    int rel_add = (int)((double)tmp_arr[0]);
                    string name = (string)tmp_arr[1];
                    byte[,] arr = (byte[,])tmp_arr[2]; // gen array             

                    int row = arr.GetLength(0);
                    int n = arr.GetLength(1);

                    UInt16 total = (UInt16)(row * n + 4);
                    byte[] tmp1 = new byte[2];
                    byte[] tmp2 = new byte[2];
                    ConvertUint16ToBytes(total, tmp1, 0);
                    ConvertUint16ToBytes((UInt16)n, tmp2, 0);

                    string var_name = string.Format("uint8_t {0}[{1}]", name, total);
                    string strArr = string.Format("{0} = {{ {1}, {2}, {3}, {4},", var_name, tmp1[0], tmp1[1], tmp2[0], tmp2[1]);
                    string strXml = string.Format("{0},{1},{2},{3},", tmp1[0], tmp1[1], tmp2[0], tmp2[1]);

                    for (int i = 0; i < row; i++)
                    {
                        strArr += "\n   ";
                        for (int j = 0; j < n; j++)
                        {
                            string tmp = Convert.ToString(arr[i, j], 10).PadLeft(3, ' ');
                            strXml += arr[i, j].ToString() + ",";
                            strArr += tmp + ", ";
                        }
                    }
                    strArr += "\n};";
                    /*
                    sw.WriteLine(strArr);
                    sw1.WriteLine("extern {0};", var_name);
                    */

                    createNode(writer, rel_add, name, strXml);
  

                    /*
                    string var_name = string.Format("uint8_t {2}[{0}][{1}]", row, n, name);

                    string strArr = string.Format("{0} = {{", var_name);
                    for (int i = 0; i < row; i++)
                    {
                        strArr += "\n   ";
                        for (int j = 0; j < n; j++)
                        {
                            string tmp = Convert.ToString(arr[i, j], 10).PadLeft(3, ' ');
                            strArr += tmp + ", ";
                        }
                    }
                    strArr += "\n};";
                    sw.WriteLine(strArr);
                    sw1.WriteLine("extern {0};", var_name);
                     */ 
                }
            }
            sw.Close();
            sw1.Close();
            fs.Close();
            fs1.Close();
            writer.WriteEndElement();
            writer.WriteEndDocument();
            writer.Close();
            MessageBox.Show("XML File created ! ");
      
        }

        private void butGenXls_Click(object sender, EventArgs e)
        {
            TableGen();
        }


        public bool ConfigParamIsChanged = false;
        public void ConfigParamsChange()
        {
            ConfigParamIsChanged = true;
        }
        public void ConfigParamsUnchange()
        {
            ConfigParamIsChanged = false;
        }
            
        private void numHeight_ValueChanged(object sender, EventArgs e)
        {
            ConfigParamsChange();
        }

        private void numWidth_ValueChanged(object sender, EventArgs e)
        {
            ConfigParamsChange();
        }

        private void txtImageFileName_TextChanged(object sender, EventArgs e)
        {
            ConfigParamsChange();
        }

        private void butConnect_Click(object sender, EventArgs e)
        {
            try
            {
                if (butConnect.Text == "Connect")
                {
                    // Checking valid config
                    if ((CbSecCom.Text == "") | (CbBaudRate.Text == ""))
                    {
                        MessageBox.Show(this, "Invalid Setting!", "Warning");
                    }
                    else
                    {
                        Ser.PortName = CbSecCom.Text;
                        int br;
                        int.TryParse(CbBaudRate.Text, out br);
                        Ser.BaudRate = br;
                        if (Ser.IsOpen)
                        {
                            MessageBox.Show("Cannot open port, Please close it first!");
                        }
                        else
                        {
                            Ser.Open();
                            butConnect.Text = "Disconnect";
                            lblStatus.Text = "Connect";
                        }
                    }
                }

                else
                {
                    Ser.Close();
                    butConnect.Text = "Connect";
                    lblStatus.Text = "Disconnect";
                }
            }
            catch
            {
                //
            }

        }

        public bool BKW_Write(byte[] dat, int len)
        {
            bool res = false;
            try
            {
                if (Ser.IsOpen)
                {
                    Ser.Write(dat, 0, len);
                    res = true;
                }
                else
                {
                    MessageBox.Show("Port is closed!");
                }
                return res;
            }
            catch
            {
                return res;
            }
        }

        public bool BKW_Read(byte[] dat, int len)
        {
            bool res = false;
            try
            {
                if (Ser.IsOpen)
                {
                    Ser.ReadTimeout = 2000; // 2000ms
                    while (Ser.BytesToRead < 4) ;
                    Ser.Read(dat, 0, len);
                    Ser.DiscardInBuffer();
                    res = true;
                }
                else
                {
                    MessageBox.Show("Port is closed or timeout!");
                }
                return res;
            }
            catch
            {
                return res;
            }
        }


        public bool BKW_ExchangeData(byte[] req, int req_len, byte[] res, int res_len)
        {
            bool ret = false;
            int count = 0;
            
            if (Ser.IsOpen)
            {
                // Request again if the transaction is fail in the first time
                while (count < 2)
                {
                    // Reset in buffer
                    Ser.DiscardInBuffer();
                    Array.Clear(res, 0, 4);
                    // Writing the request frame to BKW
                    Ser.Write(req, 0, req_len);
                    // Time out 2(sec) to get the response frame from BKW
                    var tim = Stopwatch.StartNew();
                    while (tim.ElapsedMilliseconds < 10000)
                    {
                        if (Ser.BytesToRead >= res_len)
                        {
                            // Getting the response frame
                            Ser.Read(res, 0, res_len);
                            if (BKW_DiagData(res, 4))
                            {
                                ret = true;
                                count = 100; // break the while loop
                            }
                            break;
                        }
                    }
                    count++;
                }
            }
            else
            {
                MessageBox.Show("Port is closed!");
            }
            return ret;
        }

        public bool BKW_DiagData(byte[] recv_data, int len)
        {
            bool res = false;
            if ((recv_data[0] == 0x0A) &&
                (recv_data[3] == 0x0D))
            {
                if ((recv_data[1] == (byte)'T') &&
                    (recv_data[2] == (byte)'0'))
                {
                    rtxtGen.AppendText("Correct frame");
                    res = true;
                }
                else
                {
                    rtxtGen.AppendText("Wrong frame");
                }
            }
            return res;
        }
        //const byte BKW_ID = 0x88;
        const byte BKW_ID = 0x64;
        const UInt32 CALIB_BASE_SEC = 100;
        const UInt32 SETTING_BASE_SEC = 200;
        const UInt32 SCRIPT_BASE_SEC = 300;
        const UInt32 IMAGE_BASE_SEC = 1000;
        const byte IMAGE_NUM_SEC = 10;
        const UInt32 USER_BASE_SEC = 100000;
        const UInt32 BACKUP_BASE_SEC = 110000;
        const int SECTOR_SIZE = 512;
        const string USER_PASSWORD_DEFAULT = "sgat";
        const string MASTER_PASSWORD_DEFAULT = "2013";
        //const UInt16 TOTAL_VALVE = 264;
        const UInt16 TOTAL_VALVE = 64;

        const byte MEM_AREA_SCRIPT = 3;
        const byte MEM_AREA_IMAGE = 4;

        private void butDownload_Click(object sender, EventArgs e)
        {
            /*
             * Login the system as adminstrator
             */

            if (Ser.IsOpen == false)
            {
                MessageBox.Show("Please open port first!");
                return;
            }

            if (BKW_LoginAsAdmin())
            {
                MessageBox.Show("Login as admin successfully!");
            }
            else
            {
                MessageBox.Show("Login as admin failed!");
                return;
            }
            

            /*
             * Calibrate memory
             */
            if (ckbCalibrateMem.Checked)
            {
                if (BKW_CalibrateMemory() && BKW_ReloadCalibration())
                {
                    MessageBox.Show("Calibrate & Reload memory successfully!");
                }
                else
                {
                    MessageBox.Show("Calibrate memory failed!");
                    return;
                }
            }

            /*
             * Download Images
             */
            if (ckbDownloadImg.Checked)
            {
                if (BKW_DownloadImages())
                {
                    MessageBox.Show("Download images successfully!");
                }
                else
                {
                    MessageBox.Show("Download images fail!");
                    return;
                }
            }

            /*
             * Download scripts
             */
            if (ckbDownloadSpt.Checked)
            {
                if (BKW_DownloadScripts())
                {
                    MessageBox.Show("Download scripts successfully!");
                }
                else
                {
                    MessageBox.Show("Download scripts failed!");
                    return;
                }
            }

            /*
             * LOGOUT
             */
            if (BKW_Logout())
            {
                MessageBox.Show("Logout the system: success");
            }
            else
            {
                MessageBox.Show("Logout the system: fail. The system will logout after 10sec automatically");
                return;
            }

        }


        public bool BKW_Logout()
        {
            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|8(2bytes)|0x09|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[20];
            byte[] recv_data = new byte[4];

            // Header & Command part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 8;  // length low byte
            data[4] = 0x09; // cmd code
            data[5] = 0;
            data[6] = 0;
            data[7] = 0x03;

            return BKW_ExchangeData(data, 8, recv_data, 4);
        
        }

        public bool BKW_LoginAsUser()
        {
            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|0x00|0x0C|0x02|UserPassword(4 bytes)|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[20];
            byte[] recv_data = new byte[4];

            // Header & Command part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 0x0C;  // length low byte
            data[4] = 0x02; // cmd code
            data[5] = (byte)USER_PASSWORD_DEFAULT[0]; // Master password
            data[6] = (byte)USER_PASSWORD_DEFAULT[1];
            data[7] = (byte)USER_PASSWORD_DEFAULT[2];
            data[8] = (byte)USER_PASSWORD_DEFAULT[3];
            data[9] = 0;
            data[10] = 0;
            data[11] = 0x03;

            return BKW_ExchangeData(data, 12, recv_data, 4);
        }

        public bool BKW_LoginAsAdmin()
        {
            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|0x00|0x0C|0x03|MasterPassword(4 bytes)|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[20];
            byte[] recv_data = new byte[4];

            // Header & Command part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 0x0C;  // length low byte
            data[4] = 0x03; // cmd code
            data[5] = (byte)MASTER_PASSWORD_DEFAULT[0]; // Master password
            data[6] = (byte)MASTER_PASSWORD_DEFAULT[1];
            data[7] = (byte)MASTER_PASSWORD_DEFAULT[2];
            data[8] = (byte)MASTER_PASSWORD_DEFAULT[3];
            data[9] = 0;
            data[10] = 0;
            data[11] = 0x03;

            return BKW_ExchangeData(data, 12, recv_data, 4);
        }

        public bool BKW_ReloadCalibration()
        {
            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|8(2bytes)|0x08|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[20];
            byte[] recv_data = new byte[4];

            // Header & Command part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 8;  // length low byte
            data[4] = 8; // cmd code
            data[5] = 0;
            data[6] = 0;
            data[7] = 0x03;

            return BKW_ExchangeData(data, 8, recv_data, 4);



        }

        public bool BKW_CalibrateMemory()
        {

            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|(10+i*j)(2bytes)|0x06|Sector(4bytes)|
             * Data(multi-bytes)|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[1000];
            byte[] recv_data = new byte[4];
            int len = 0;
            int ind = 0;

            // Header & Command part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 0;  // length low byte
            data[4] = 0x06; // cmd code
            ind = 5;
            ConvertUint32ToBytes(CALIB_BASE_SEC, data, ind);
            ind += 4;

            /*****************************************************************
             * Area 1: Calibration
             *****************************************************************/

            // data part
            data[ind++] = (byte)'A';
            data[ind++] = (byte)'C';
            data[ind++] = (byte)'A';
            data[ind++] = (byte)'L';

            ConvertUint32ToBytes(SETTING_BASE_SEC, data, ind);
            ind += 4;
            ConvertUint32ToBytes(SCRIPT_BASE_SEC, data, ind);
            ind += 4;
            ConvertUint32ToBytes(IMAGE_BASE_SEC, data, ind);
            ind += 4;
            ConvertUint32ToBytes(USER_BASE_SEC, data, ind);
            ind += 4;
            ConvertUint32ToBytes(BACKUP_BASE_SEC, data, ind);
            ind += 4;
            data[ind++] = 0x00; //CRC1
            data[ind++] = 0x00; //CRC2
            data[ind] = 0x03;
            len = ind + 1;
            byte[] tmp = new byte[4];
            ConvertUint32ToBytes((UInt32)len, tmp, 0);
            data[2] = tmp[2];
            data[3] = tmp[3];
            
            rtxtGen.AppendText("Download to area calibration:");
            if (!BKW_ExchangeData(data, len, recv_data, 4))
            {
                rtxtGen.AppendText("Fail");
                return false;
            }

            /*****************************************************************
             * Area 2: Setting
             *****************************************************************/
            ind = 5;
            ConvertUint32ToBytes(SETTING_BASE_SEC, data, ind);
            ind += 4;

            // data part
            data[ind++] = (byte)'A';
            data[ind++] = (byte)'S';
            data[ind++] = (byte)'E';
            data[ind++] = (byte)'T';

            data[ind++] = (byte)USER_PASSWORD_DEFAULT[0];
            data[ind++] = (byte)USER_PASSWORD_DEFAULT[1];
            data[ind++] = (byte)USER_PASSWORD_DEFAULT[2];
            data[ind++] = (byte)USER_PASSWORD_DEFAULT[3];
            ConvertUint32ToBytes(TOTAL_VALVE, tmp, 0);
            data[ind++] = tmp[2];
            data[ind++] = tmp[3];

            // footer part
            data[ind++] = 0x00; //CRC1
            data[ind++] = 0x00; //CRC2
            data[ind] = 0x03;
            len = ind + 1;
            // update length of the frame
            ConvertUint32ToBytes((UInt32)len, tmp, 0);
            data[2] = tmp[2];
            data[3] = tmp[3];
            // send to BKW
            rtxtGen.AppendText("Download to area setting:");
            if (!BKW_ExchangeData(data, len, recv_data, 4))
            {
                rtxtGen.AppendText("Fail");
                return false;
            }

            /*****************************************************************
             * Area 3: Script
             *****************************************************************/
            ind = 5;
            ConvertUint32ToBytes(SCRIPT_BASE_SEC, data, ind);
            ind += 4;

            // Data part
            data[ind++] = (byte)'A';
            data[ind++] = (byte)'S';
            data[ind++] = (byte)'P';
            data[ind++] = (byte)'T';

            data[ind++] = 0; // Number of scripts
            data[ind++] = 0;

            // footer part
            data[ind++] = 0x00; //CRC1
            data[ind++] = 0x00; //CRC2
            data[ind] = 0x03; //ETX
            len = ind + 1;
            // update length of the frame
            ConvertUint32ToBytes((UInt32)len, tmp, 0);
            data[2] = tmp[2];
            data[3] = tmp[3];

            // send to BKW
            rtxtGen.AppendText("Download to area script:");
            if (!BKW_ExchangeData(data, len, recv_data, 4))
            {
                rtxtGen.AppendText("Fail");
                return false;
            }

            /*****************************************************************
             * Area 4: Image
             *****************************************************************/
            ind = 5;
            ConvertUint32ToBytes(IMAGE_BASE_SEC, data, ind);
            ind += 4;

            // Data part
            data[ind++] = (byte)'A';
            data[ind++] = (byte)'I';
            data[ind++] = (byte)'M';
            data[ind++] = (byte)'G';

            data[ind++] = 0; // Number of images
            data[ind++] = 0;
            data[ind++] = IMAGE_NUM_SEC; // number sector per image

            // footer part
            data[ind++] = 0x00; //CRC1
            data[ind++] = 0x00; //CRC2
            data[ind] = 0x03; //ETX
            len = ind + 1;
            // update length of the frame
            ConvertUint32ToBytes((UInt32)len, tmp, 0);
            data[2] = tmp[2];
            data[3] = tmp[3];

            // send to BKW
            rtxtGen.AppendText("Download to area image:");
            if (!BKW_ExchangeData(data, len, recv_data, 4))
            {
                rtxtGen.AppendText("Fail");
                return false;
            }

            /*
             * Area 5: User
             * For future use
             */

            /*
             * Area 6: Backup
             * For future use
             */

            return true;
        }

        public bool BKW_DownloadImages()
        {

            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|(11+i*j)(2bytes)|0x07|
             *                    |Address(2bytes)|Area(1byte)|Data(multi-bytes)|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[10000];
            byte[] recv_data = new byte[4];
            int len = 0;
            int ind = 0;

            /*
             * Get Xml file
             */
            XmlReader reader;
            string path = WorkFolderName + "\\table.xml";
            if (File.Exists(path))
            {
                reader = XmlReader.Create(path);
            }
            else
            {
                MessageBox.Show("Please add the working directory!");
                return false;
            }

            while (reader.Read())
            {
                int rel_add;
                int l;
                string img;
                if ((reader.Name == "Image") && (int.TryParse(reader.GetAttribute("address"), out rel_add)))
                {
                    img = reader.ReadInnerXml();
                    // Header & Command part
                    data[0] = 0x02;
                    data[1] = BKW_ID;
                    data[2] = 0;  // length high byte
                    data[3] = 0;  // length low byte
                    data[4] = 0x07; // cmd code
                    ind = 5; 
                    // relative address
                    ConvertUint16ToBytes((UInt16)rel_add, data, ind);
                    ind += 2;
                    data[ind++] = MEM_AREA_IMAGE;

                    ConvertCsvToBytes(img, data, ind, out l);
                    ind += l;
                    
                    // footer part
                    data[ind++] = 0x00; //CRC1
                    data[ind++] = 0x00; //CRC2
                    data[ind] = 0x03; //ETX
                    len = ind + 1;
                    // update length of the frame
                    ConvertUint16ToBytes((UInt16)len, data, 2); // update len

                    if (!BKW_ExchangeData(data, len, recv_data, 4))
                    {
                        rtxtGen.AppendText(string.Format("\nDownload image to address {0}: fail", rel_add));
                        return false;
                    }
                    rtxtGen.AppendText(string.Format("\nDownload image to address {0}: Success", rel_add));
                }
            }
            return true;
        }

        public bool BKW_DownloadScripts()
        {

            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|(11+i*j)(2bytes)|0x07|
             *                    |Address(2bytes)|Area(1byte)||Data(multi-bytes)|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[1000];
            byte[] recv_data = new byte[4];
            int spt_count = 0;
            int len = 0;
            int ind = 0;


            /*
             * Get Xml file
             */
            XmlReader reader;
            if (File.Exists(WorkFolderName + "\\script.xml"))
            {
                reader = XmlReader.Create(WorkFolderName + "\\script.xml");
            }
            else
            {
                MessageBox.Show("Please add the working directory!");
                return false;
            }

            while (reader.Read())
            {
                int rel_add;
                int l;
                string spt;
                if ((reader.Name == "Script") && (int.TryParse(reader.GetAttribute("address"), out rel_add)))
                {
                    spt = reader.ReadInnerXml();
                    // Header & Command part
                    data[0] = 0x02;
                    data[1] = BKW_ID;
                    data[2] = 0;  // length high byte
                    data[3] = 0;  // length low byte
                    data[4] = 0x07; // cmd code
                    ind = 5;
                    // relative address
                    ConvertUint16ToBytes((UInt16)rel_add, data, ind);
                    ind += 2;
                    data[ind++] = MEM_AREA_SCRIPT;

                    ConvertCsvToBytes(spt, data, ind, out l);
                    ind = ind+l;

                    // footer part
                    data[ind++] = 0x00; //CRC1
                    data[ind++] = 0x00; //CRC2
                    data[ind] = 0x03; //ETX
                    len = ind + 1;
                    // update length of the frame
                    ConvertUint16ToBytes((UInt16)len, data, 2); // update len

                    
                    if (!BKW_ExchangeData(data, len, recv_data, 4))
                    {
                        rtxtGen.AppendText(string.Format("Download script to address {0}: fail", rel_add));
                        return false;
                    }
                    spt_count++;
                    //rtxtGen.AppendText(string.Format("Download image to address {0}: Success", rel_add));
                }
            }

            // Header & Command part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 0;  // length low byte
            data[4] = 0x07; // cmd code
            ind = 5;
            // relative address
            ConvertUint16ToBytes(0, data, ind); // config the number of scripts
            ind += 2;
            data[ind++] = MEM_AREA_SCRIPT;
            data[ind++] = (byte)'A';
            data[ind++] = (byte)'S';
            data[ind++] = (byte)'P';
            data[ind++] = (byte)'T';

            ConvertUint16ToBytes((UInt16)spt_count, data, ind);
            ind += 2;

            // footer part
            data[ind++] = 0x00; //CRC1
            data[ind++] = 0x00; //CRC2
            data[ind] = 0x03; //ETX
            len = ind + 1;
            // update length of the frame
            ConvertUint16ToBytes((UInt16)len, data, 2); // update len

            if (!BKW_ExchangeData(data, len, recv_data, 4))
            {
                rtxtGen.AppendText(string.Format("Download script number ({0}) to address 0: fail", spt_count));
                return false;
            }

            rtxtGen.AppendText(string.Format("Download script number ({0}) to address 0: success", spt_count));

            return true;
        }

        public void ConvertCsvToBytes(string s, byte[] b, int offset, out int len)
        {
            len = 0;
            int k = 0;
            string[] sArr = s.Split(',');
            for (int i = 0; i < sArr.Length; i++)
            {
                if (sArr[i].Length != 0)
                {
                    b[offset + k] = Convert.ToByte(sArr[i]);
                    k++;
                }
            }
            len = k;
        }

        public void ConvertUint32ToBytes(UInt32 u, byte[] b, int offset)
        {
            for (int i = 0; i < 4; i++)
            {
                b[offset + i] = (byte)((u >> (24 - 8 * i)) & 0xff);
            }
        }

        public void ConvertUint16ToBytes(UInt16 u, byte[] b, int offset)
        {
            for (int i = 0; i < 2; i++)
            {
                b[offset + i] = (byte)((u >> (8 - 8 * i)) & 0xff);
            }
        }

        public void String2Bytes(string s, byte[] b, out int len)
        {
            len = 0;
            int k = 0;
            string[] sArr = s.Split(',');
            for (int i = 0; i < sArr.Length; i++)
            {
                if (sArr[i].Length != 0)
                {
                    b[k++] = Convert.ToByte(sArr[i]);
                }
            }
            len = k;
        }

        private void butCalibMem_Click(object sender, EventArgs e)
        {
            /*
             *  LOG IN SYSTEM AS ADMIN
             */
            if (BKW_LoginAsAdmin())
            {
                MessageBox.Show("Log in system as admin: success");
            }
            else
            {
                MessageBox.Show("Log in is failed. Please recheck your password");
            }

            /*
             *  CALIBRATE THE MEMORY FIRSTLY
             */
            if (BKW_CalibrateMemory())
            {
                MessageBox.Show("Download to memory: success");
            }
            else
            {
                MessageBox.Show("Download is failed. Please check your cable and reset the system");
                return;
            }

            /*
             * Reload memory
             */
            if (BKW_ReloadCalibration())
            {
                MessageBox.Show("Reload memory: successful");
            }
            else
            {
                MessageBox.Show("Reload memory: fail");
                return;
            }
        }

        private void butOpenWorkDir_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folder = new FolderBrowserDialog();
            if (Directory.Exists("C:\\Users\\daiba\\OneDrive - Ho Chi Minh city University of Food Industry\\Desktop\\Script"))
            {
                folder.SelectedPath = "C:\\Users\\daiba\\OneDrive - Ho Chi Minh city University of Food Industry\\Desktop\\Script";
            }
            if (folder.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                txtWorkDir.Text = folder.SelectedPath;
                WorkFolderName = txtWorkDir.Text;
                ImagesFolderName = WorkFolderName + "\\Images\\";
                TableFileName = WorkFolderName + "\\BKWTable.xlsm";
            }
        }

        BKW_ScriptEditor SptEditor;
        ArrayList SptList;
        byte[,] SptArr;
        int SptInd;
        int USptInd;
        private void butNewScript_Click(object sender, EventArgs e)
        {
            SptArr = new byte[20, 30];
            SptInd = -1;
            USptInd = -1;

            SptList = new ArrayList();
            
            SptEditor = new BKW_ScriptEditor();
            SptEditor.Location = new System.Drawing.Point(1060, 30);
            SptEditor.Size = new Size(400, 620);
            this.Controls.Add(SptEditor);

        }

        public int GridRowIndex;
        private void dataView_RowEnter(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                string fn = ImagesFolderName + dataView.Rows[e.RowIndex].Cells[1].Value.ToString() + ".bmp";
                string fn1 = ImagesFolderName + dataView.Rows[e.RowIndex].Cells[1].Value.ToString() + ".png";
                if (File.Exists(fn1)) fn = fn1;
                if (File.Exists(fn))
                {
                    picBox.Image = Image.FromFile(fn);
                    GridRowIndex = e.RowIndex;
                }
                rtxtGen.Text += e.RowIndex.ToString();
            }
            catch
            {
                return;
            }
        }

        const double WIDTH_MAX = 2904; //3m
        const double HEIGHT_MAX = 3000;
        private void butNewUScript_Click(object sender, EventArgs e)
        {
            SptInd++;
            USptInd = 1;
            /* Select from data grid view */
            string name = dataView.Rows[GridRowIndex].Cells[1].Value.ToString();
            string fn = ImagesFolderName + name + ".bmp";
            string fn1 = ImagesFolderName + name + ".png";
            if (File.Exists(fn1)) fn = fn1;
            double w = (double)dataView.Rows[GridRowIndex].Cells[2].Value;
            double h = (double)dataView.Rows[GridRowIndex].Cells[3].Value;
            BKW_Pic pic = new BKW_Pic(name, fn, true);
            SptEditor.AddNewImage(pic, true, w/WIDTH_MAX, h/HEIGHT_MAX);

            SptList.Add(pic);

            double d = (double)dataView.Rows[GridRowIndex].Cells[0].Value;
            SptArr[SptInd, USptInd++] = (byte)(((UInt16)d >> 8) & 0xff);
            SptArr[SptInd, USptInd++] = (byte)(((UInt16)d) & 0xff);
            SptArr[SptInd, 0] += 2;
            
        }

        private void butNewImage_Click(object sender, EventArgs e)
        {
            /* Select from data grid view */
            try
            {
                string name = dataView.Rows[GridRowIndex].Cells[1].Value.ToString();
                string fn = ImagesFolderName + name + ".bmp";
                string fn1 = ImagesFolderName + name + ".png";
                if (File.Exists(fn1)) fn = fn1;
                double w = (double)dataView.Rows[GridRowIndex].Cells[2].Value;
                double h = (double)dataView.Rows[GridRowIndex].Cells[3].Value;
                BKW_Pic pic = new BKW_Pic(name, fn, false);
                SptEditor.AddNewImage(pic, false, w / WIDTH_MAX, h / HEIGHT_MAX);

                double d = (double)dataView.Rows[GridRowIndex].Cells[0].Value;
                SptArr[SptInd, USptInd++] = (byte)(((UInt16)d >> 8) & 0xff);
                SptArr[SptInd, USptInd++] = (byte)(((UInt16)d) & 0xff);
                SptArr[SptInd, 0] += 2;
            }
            catch
            {

            }

        }


        private void butDeleteScript_Click(object sender, EventArgs e)
        {
            SptEditor.Delete();

        }

        private void butSaveScript_Click(object sender, EventArgs e)
        {
            //string path_save = WorkFolderName + "\\spt.txt";
            //File.WriteAllText(path_save, "");
            StreamWriter sw = new StreamWriter(WorkFolderName + "\\spt.txt", true);
            sw.WriteLine("\nScript New\n");

            int i, j, k;
            byte[] mes = new byte[400];
            mes[0] = (byte)(SptInd + 1); // Number of Unit Script
            mes[1] = SptEditor.GetRepeat();
            int offset = 2;
            for (i = 0; i <= SptInd; i++)
            {
                mes[offset + 0] = 0x02; // STX
                mes[offset + 1] = (byte)(8 + SptArr[i, 0]); // Length
                mes[offset + 2] = 0x01;
                for (j = 0; j < SptArr[i, 0]; j++)
                {
                    mes[offset + 3 + j] = SptArr[i, j+1];
                }
                int add = ((mes[offset + 3 + 0] << 8) + mes[offset + 3 + 1]);
                // Searching in table
                string name = "";
                for (k = 0; k < dataView.Rows.Count; k++)
                {
                    if (dataView.Rows[k].Cells[0].Value != null)
                    {
                        if ((double)dataView.Rows[k].Cells[0].Value == (double)add)
                        {
                            name = dataView.Rows[k].Cells[1].Value.ToString();
                            break;
                        }
                    }
                }

                // Searching in image list
                for (k = 0; k < SptList.Count; k++)
                {
                    BKW_Pic p = (BKW_Pic)SptList[k];
                    if (p.name == name)
                    {
                        conf = p.conf;
                        mes[offset + 3 + j] = (byte)conf.align;
                        mes[offset + 4 + j] = (byte)conf.repeat;
                        mes[offset + 5 + j] = (byte)conf.dlbefore;
                        mes[offset + 6 + j] = (byte)conf.dlrepeat;
                        mes[offset + 7 + j] = (byte)conf.dlafter;
                    }
                }
                offset += mes[offset + 1]; // move the offset to new unit script
            }
            
            string myXml = "";
            for (i = 0;  i < offset; i++)
            {
                //sw.Write(mes[i]);
                //sw.Write(',');
                myXml += mes[i].ToString() + ',';
            }

            sw.Close();

            /*
             * Reference: http://www.dreamincode.net/forums/topic/49289-working-with-xml-files-in-c%23-part-2/
             */ 
            //The path to our config file
            string path = WorkFolderName + "\\script.xml";
            string path1 = WorkFolderName + "\\script_new.txt";
            string [] data_file_new = File.ReadAllLines(path1);

            //create the reader filestream (fs)
            if (!File.Exists(path))
            {
                FileStream fs_new = new FileStream(path, FileMode.Create, FileAccess.ReadWrite, FileShare.ReadWrite);
                fs_new.Close();
                File.WriteAllLines(path, data_file_new);
            }
            else
            {
                File.WriteAllLines(path, data_file_new);
            }
            FileStream fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);

            //Create the xml document
            System.Xml.XmlDocument CXML = new System.Xml.XmlDocument();

            //Load the xml document
            CXML.Load(fs);

            //Close the fs filestream
            fs.Close();

            // create the new element (node)
            XmlElement newitem = CXML.CreateElement("Script");
            newitem.SetAttribute("address", (CXML.DocumentElement.ChildNodes.Count + 1).ToString());
            newitem.SetAttribute("name", SptEditor.GetName());

            // Put the value (inner Text) into the node
            newitem.InnerText = myXml;

            //Insert the new XML Element into the main xml document (CXML)
            CXML.DocumentElement.InsertAfter(newitem, CXML.DocumentElement.LastChild);

            //Save the XML file
            FileStream WRITER = new FileStream(path, FileMode.Truncate, FileAccess.Write, FileShare.ReadWrite);
            CXML.Save(WRITER);

            //Close the writer filestream
            WRITER.Close();

        }

        private void butSend_Click(object sender, EventArgs e)
        {
            /*
             * Download scripts
             */

            if (BKW_DownloadScripts())
            {
                MessageBox.Show("Download scripts successfully!");
            }
            else
            {
                MessageBox.Show("Download scripts failed!");
                return;
            }
        }

        int portnum;
        private void SerTimer_Tick(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames(); //lay tat ca cong COM trong PC
            if (portnum != ports.Length)
            {
                portnum = ports.Length;
                CbSecCom.Items.Clear();
                for (int j = 0; j < portnum; j++)
                {
                    CbSecCom.Items.Add(ports[j]);
                }
            }
        }

        private void butDispImg_Click(object sender, EventArgs e)
        {
            if (butLogin.Text != "Logout")
            {
                MessageBox.Show("Please login as first!");
                return;
            }

            /*
            * Display an image
            */
            if (BKW_DisplayImage())
            {
                MessageBox.Show("Download images successfully!");
            }
            else
            {
                MessageBox.Show("Download images fail!");
                return;
            }

        }

        bool BKW_DisplayImage()
        {

            /* 
             * The transaction is started by the request frame from PC and is ended by 
             * response frame from BKW system
             * --> Request Frame: |0x02|BKWID(1byte)|(10+n)(2bytes)|0x05|T(x20ms)(1 byte)|N(1 byte)|
             *                    |Image(n bytes)|CRC(2bytes)|0x03|
             * <-- Response frame: 
             * |0x0A|'T'|'0'|0x0D|: successful
             */

            byte[] data = new byte[10000];
            byte[] recv_data = new byte[4];
            int len = 0;
            int ind = 0;

            int row = WarArray.GetLength(0); // number of rows
            int n = WarArray.GetLength(1);  // number of columns
            UInt16 total = (UInt16)(row * n + 4);
            
            // header part
            data[0] = 0x02;
            data[1] = BKW_ID;
            data[2] = 0;  // length high byte
            data[3] = 0;  // length low byte
            data[4] = 0x05; // cmd code
            data[5] = 30; // delay 30x20ms
            data[6] = 2; // repeat 2 times
            ind = 7;

            // load the image:|total|number-col|data|
            ConvertUint16ToBytes(total, data, ind);
            ind += 2;
            ConvertUint16ToBytes((UInt16)n, data, ind);
            ind += 2;
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    data[ind++] = WarArray[i, j];
                }
            }

            // footer part
            data[ind++] = 0x00; //CRC1
            data[ind++] = 0x00; //CRC2
            data[ind] = 0x03; //ETX
            len = ind + 1;
            // update length of the frame
            ConvertUint16ToBytes((UInt16)len, data, 2); // update len

            if (!BKW_ExchangeData(data, len, recv_data, 4))
            {
                rtxtGen.AppendText("Download image to display is failed!");
                return false;
            }
            rtxtGen.AppendText("Download image to display is successful!");
            return true;
        }

        private void butLogin_Click(object sender, EventArgs e)
        {
            if (Ser.IsOpen == false)
            {
                MessageBox.Show("Please open port first!");
                return;
            }
            int password = Convert.ToInt16(txtPassword.Text);
            if (butLogin.Text == "Login")
            {
                if (password == 2013)
                {
                    if (BKW_LoginAsUser())
                    {
                        MessageBox.Show("Login as user successfully!");
                        butLogin.Text = "Logout";
                    }
                    else
                    {
                        MessageBox.Show("Login as user failed!");
                    }
                }
                else
                {
                    MessageBox.Show("Error Password");
                }
            }
            else
            {
                if (BKW_Logout())
                {
                    MessageBox.Show("Logout successfully!");
                }
                else
                {
                    MessageBox.Show("Logout failed! Logout anyway");
                }
                butLogin.Text = "Login";
            }
        }

        private void tabPage8_Click(object sender, EventArgs e)
        {

        }

        private void pnGrid_Paint(object sender, PaintEventArgs e)
        {

        }

        private void rtxtGen_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void lblSlider_Click(object sender, EventArgs e)
        {

        }

        private void bt_SendImage_Click(object sender, EventArgs e)
        {
            if (butLogin.Text != "Logout")
            {
                MessageBox.Show("Please login as first!");
                return;
            }

            /*
            * Display an image
            */
            if (BKW_DisplayImage())
            {
                MessageBox.Show("Download images successfully!");
            }
            else
            {
                MessageBox.Show("Download images fail!");
                return;
            }
        }
    }

    public class BKW_Pic : System.Windows.Forms.PictureBox, IScriptConf
    {
        static object[,] picList;
        static Random rd;
        static int count;

        public int id;
        public string name;
        private string filepath;
        private string xml;
        public IScriptConfDef.UScriptParams conf;

        private ToolTip tt;
        private ContextMenuStrip cms;
        private ToolStripMenuItem deleteToolStripMenuItem;
        private ToolStripMenuItem editToolStripMenuItem;

        // Constructor
        public BKW_Pic(string n, string fp, bool enable)
        {
            /* Image setting */
            this.BackColor = Color.Blue;
            this.Size = new System.Drawing.Size(80, 60);
            this.SizeMode = PictureBoxSizeMode.StretchImage;
            

            /* This handlers */
            if (enable == true)
            {
                
                //this.Click += new EventHandler(BKW_Pic_Click);
                this.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
                //this.MouseDown += new MouseEventHandler(BKW_Pic_MouseDown);
                //this.MouseMove += new MouseEventHandler(BKW_Pic_MouseMove);
                //this.MouseUp += new MouseEventHandler(BKW_Pic_MouseUp);

                cms = new ContextMenuStrip();
                deleteToolStripMenuItem = new ToolStripMenuItem("Delete");
                deleteToolStripMenuItem.Click += new EventHandler(deleteToolStripMenuItem_Click);
                editToolStripMenuItem = new ToolStripMenuItem("Edit");
                editToolStripMenuItem.Click += new EventHandler(editToolStripMenuItem_Click);
                cms.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {editToolStripMenuItem, deleteToolStripMenuItem });
                this.ContextMenuStrip = cms;

            }
            /* This tooltips */
            this.MouseHover += new EventHandler(BKW_Pic_MouseHover);
            tt = new ToolTip();
            
            /* Parameters */
            if (File.Exists(fp))
            {
                name = n;
                filepath = fp;
                this.Image = Image.FromFile(fp);
                /*
                if (picList == null)
                {
                    rd = new Random();
                    picList = new object[20, 2];
                    count = 0;
                }
                 * *
                else
                {
                    count++;
                }
                double d = rd.NextDouble() * 1000;
                id = (int)d;
                picList[count, 0] = id;
                picList[count, 1] = this;
                 */
            }
        }

        public UScriptParams usc
        {
            set
            {
                conf.repeat = value.repeat;
                conf.dlbefore = value.dlbefore;
                conf.dlrepeat = value.dlrepeat;
                conf.dlafter = value.dlafter;
                conf.align = value.align;
            }

            get
            {
                return conf;
            }
        }

        void editToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form f = new ScripConfForm();
            f.Load += new EventHandler(f_Load);
            f.FormClosed += new FormClosedEventHandler(f_FormClosed);
            f.Show();
        }

        void f_Load(object sender, EventArgs e)
        {
            ScripConfForm f = sender as ScripConfForm;
            f.usc = conf;
        }

        void f_FormClosed(object sender, FormClosedEventArgs e)
        {
            ScripConfForm f = sender as ScripConfForm;
            conf = f.usc;
            f.Dispose();
        }

        void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        void BKW_Pic_MouseUp(object sender, MouseEventArgs e)
        {
            dragging = false;
        }

        void BKW_Pic_MouseMove(object sender, MouseEventArgs e)
        {
            if (dragging)
                this.Location = new Point(this.Location.X + e.X - dragPoint.X, this.Location.Y + e.Y - dragPoint.Y);
        }

        void BKW_Pic_MouseDown(object sender, MouseEventArgs e)
        {
            dragging = true;
            dragPoint = new Point(e.X, e.Y);
        }

        void BKW_Pic_MouseHover(object sender, EventArgs e)
        {
            tt.SetToolTip(this, name + '\n' + filepath);
        }

        void BKW_Pic_Click(object sender, EventArgs e)
        {
            this.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
        }

        Point dragPoint = Point.Empty;
        bool dragging = false;

    }

    public class BKW_ScriptEditor : System.Windows.Forms.Panel
    {
        // 
        //public string name;

        // Controls
        private System.Windows.Forms.VScrollBar vsb;
        private System.Windows.Forms.Label lb;
        private System.Windows.Forms.TextBox tb;
        private System.Windows.Forms.NumericUpDown nb;
        
        // Variables
        private int numRow;
        private int uHeight;
        private int uWidth;
        private int h_1, u_1;
        private struct Position
        {
            public int x;
            public int y;
        }
        Position posCur;


        public BKW_ScriptEditor()
        {
            /* Variables */
            posCur = new Position();

            /* Controls */
            this.BackColor = System.Drawing.Color.Silver;

            lb = new Label();
            tb = new TextBox();
            nb = new NumericUpDown();

            // 
            // lb
            // 
            this.lb.Location = new System.Drawing.Point(0, 10);
            this.lb.Name = "lb";
            this.lb.Size = new System.Drawing.Size(80, 13);
            this.lb.Text = "Name/Repeat";
            // 
            // tb
            // 
            this.tb.Location = new System.Drawing.Point(81, 7);
            this.tb.Name = "tb";
            this.tb.Size = new System.Drawing.Size(70, 20);
            //
            // nb
            //
            this.nb.Location = new System.Drawing.Point(160, 7);
            this.nb.Name = "nb";
            this.nb.Size = new System.Drawing.Size(70, 20);
            this.nb.Maximum = 200;
            //this.nb.Value = 0;

            this.Controls.Add(this.lb);
            this.Controls.Add(this.tb);
            this.Controls.Add(this.nb);

            /* Handlers */
            //this.ControlAdded += new ControlEventHandler(BKW_ScriptEditor_ControlAdded);

        }

        public string GetName()
        {
            return tb.Text;
        }

        public byte GetRepeat()
        {
            return (byte)nb.Value;
        }

        protected override void InitLayout()
        {
            base.InitLayout();
            this.VerticalScroll.Visible = true;
            this.HorizontalScroll.Visible = true;
            this.AutoScroll = true;
            //this.AddVScrollBar();
            uHeight = this.Height/2;
            uWidth = this.Width * 2;
            h_1 = 40;
            u_1 = 0;
        }

        public void AddNewImage(PictureBox c, bool new_row, double w_ratio, double h_ratio)
        {
            
            this.VerticalScroll.Value = 0;
            this.HorizontalScroll.Value = 0;
            c.Height = (int)((double)(h_ratio * uHeight));
            c.Width = (int)((double)(w_ratio * uWidth));
            u_1 = c.Width;
            if (new_row)
            {
                numRow++;
                posCur.x = 0;
                posCur.y += h_1;
                //this.DrawNewUscript();
            }
            h_1 = c.Height;
            c.Location = new Point(posCur.x, posCur.y);
            posCur.x += c.Width;
            this.Controls.Add(c);
            this.ScrollControlIntoView(c);
        }

        private void DrawNewUscript()
        {
            System.Drawing.Pen penRed;
            penRed = new System.Drawing.Pen(System.Drawing.Color.Red, 5);
            System.Drawing.Graphics editor = this.CreateGraphics();
            // Draw grid
            editor.DrawLine(penRed, 0, posCur.y, this.Width, posCur.y);
        }

        public void Delete()
        {
            this.Dispose();
        }

        private void AddVScrollBar()
        {
            vsb = new VScrollBar();
            vsb.Dock = DockStyle.Right;
            vsb.Scroll += (sender, e) => { this.VerticalScroll.Value = vsb.Value; };
            this.Controls.Add(this.vsb);
        }

        
    }
}
