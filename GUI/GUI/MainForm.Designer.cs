namespace BKWGen3
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.butOpen = new System.Windows.Forms.Button();
            this.pnGrid = new System.Windows.Forms.Panel();
            this.slider = new System.Windows.Forms.TrackBar();
            this.lblSlider = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.numWidth = new System.Windows.Forms.NumericUpDown();
            this.numHeight = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.ckbNegative = new System.Windows.Forms.CheckBox();
            this.butGen = new System.Windows.Forms.Button();
            this.lblStatus = new System.Windows.Forms.Label();
            this.dataView = new System.Windows.Forms.DataGridView();
            this.butConnect = new System.Windows.Forms.Button();
            this.Ser = new System.IO.Ports.SerialPort(this.components);
            this.txtPassword = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.butOpenWorkDir = new System.Windows.Forms.Button();
            this.txtWorkDir = new System.Windows.Forms.TextBox();
            this.txtImageFileName = new System.Windows.Forms.TextBox();
            this.butOpenXls = new System.Windows.Forms.Button();
            this.butSaveScript = new System.Windows.Forms.Button();
            this.butDeleteScript = new System.Windows.Forms.Button();
            this.butNewImage = new System.Windows.Forms.Button();
            this.butNewUScript = new System.Windows.Forms.Button();
            this.butNewScript = new System.Windows.Forms.Button();
            this.Tim100ms = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.picBox = new System.Windows.Forms.PictureBox();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabConnect = new System.Windows.Forms.TabPage();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.butLogin = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label18 = new System.Windows.Forms.Label();
            this.CbBaudRate = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.CbSecCom = new System.Windows.Forms.ComboBox();
            this.tabSend1Picture = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label8 = new System.Windows.Forms.Label();
            this.ckbLoadImg = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.ckbReverseImage = new System.Windows.Forms.CheckBox();
            this.bt_SendImage = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tabCreatScript = new System.Windows.Forms.TabPage();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.butDownload = new System.Windows.Forms.Button();
            this.ckbDownloadSpt = new System.Windows.Forms.CheckBox();
            this.ckbDownloadImg = new System.Windows.Forms.CheckBox();
            this.ckbCalibrateMem = new System.Windows.Forms.CheckBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.tabData1Picture = new System.Windows.Forms.TabPage();
            this.rtxtGen = new System.Windows.Forms.RichTextBox();
            this.tabAbout = new System.Windows.Forms.TabPage();
            this.textBoxDescription = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.logoPictureBox = new System.Windows.Forms.PictureBox();
            this.SerTimer = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.slider)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataView)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox)).BeginInit();
            this.tabControl2.SuspendLayout();
            this.tabConnect.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.tabSend1Picture.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.tabCreatScript.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.tabData1Picture.SuspendLayout();
            this.tabAbout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.logoPictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // butOpen
            // 
            this.butOpen.BackColor = System.Drawing.SystemColors.Control;
            this.butOpen.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butOpen.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butOpen.Location = new System.Drawing.Point(314, 28);
            this.butOpen.Margin = new System.Windows.Forms.Padding(4);
            this.butOpen.Name = "butOpen";
            this.butOpen.Size = new System.Drawing.Size(66, 31);
            this.butOpen.TabIndex = 1;
            this.butOpen.Text = "Browse";
            this.butOpen.UseVisualStyleBackColor = false;
            this.butOpen.Click += new System.EventHandler(this.butOpen_Click);
            // 
            // pnGrid
            // 
            this.pnGrid.BackColor = System.Drawing.Color.Gray;
            this.pnGrid.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pnGrid.Location = new System.Drawing.Point(4, 228);
            this.pnGrid.Margin = new System.Windows.Forms.Padding(4);
            this.pnGrid.Name = "pnGrid";
            this.pnGrid.Size = new System.Drawing.Size(637, 395);
            this.pnGrid.TabIndex = 4;
            this.pnGrid.Paint += new System.Windows.Forms.PaintEventHandler(this.pnGrid_Paint);
            // 
            // slider
            // 
            this.slider.LargeChange = 3;
            this.slider.Location = new System.Drawing.Point(75, 218);
            this.slider.Margin = new System.Windows.Forms.Padding(4);
            this.slider.Maximum = 255;
            this.slider.Name = "slider";
            this.slider.Size = new System.Drawing.Size(305, 45);
            this.slider.TabIndex = 3;
            this.slider.TickStyle = System.Windows.Forms.TickStyle.None;
            this.slider.Value = 125;
            this.slider.Scroll += new System.EventHandler(this.slider_Scroll);
            // 
            // lblSlider
            // 
            this.lblSlider.AutoSize = true;
            this.lblSlider.BackColor = System.Drawing.Color.White;
            this.lblSlider.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblSlider.Location = new System.Drawing.Point(31, 218);
            this.lblSlider.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSlider.Name = "lblSlider";
            this.lblSlider.Size = new System.Drawing.Size(29, 16);
            this.lblSlider.TabIndex = 4;
            this.lblSlider.Text = "125";
            this.lblSlider.Click += new System.EventHandler(this.lblSlider_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(8, 180);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Threshold";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(44, 92);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Width (mm)";
            // 
            // numWidth
            // 
            this.numWidth.Location = new System.Drawing.Point(48, 118);
            this.numWidth.Margin = new System.Windows.Forms.Padding(4);
            this.numWidth.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numWidth.Name = "numWidth";
            this.numWidth.Size = new System.Drawing.Size(95, 20);
            this.numWidth.TabIndex = 7;
            this.numWidth.Value = new decimal(new int[] {
            960,
            0,
            0,
            0});
            this.numWidth.ValueChanged += new System.EventHandler(this.numWidth_ValueChanged);
            // 
            // numHeight
            // 
            this.numHeight.Location = new System.Drawing.Point(236, 118);
            this.numHeight.Margin = new System.Windows.Forms.Padding(4);
            this.numHeight.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numHeight.Name = "numHeight";
            this.numHeight.Size = new System.Drawing.Size(95, 20);
            this.numHeight.TabIndex = 8;
            this.numHeight.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numHeight.ValueChanged += new System.EventHandler(this.numHeight_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(232, 92);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Height (mm)";
            // 
            // ckbNegative
            // 
            this.ckbNegative.AutoSize = true;
            this.ckbNegative.Location = new System.Drawing.Point(35, 339);
            this.ckbNegative.Margin = new System.Windows.Forms.Padding(4);
            this.ckbNegative.Name = "ckbNegative";
            this.ckbNegative.Size = new System.Drawing.Size(115, 17);
            this.ckbNegative.TabIndex = 10;
            this.ckbNegative.Text = "Negative Image";
            this.ckbNegative.UseVisualStyleBackColor = true;
            // 
            // butGen
            // 
            this.butGen.BackColor = System.Drawing.Color.SandyBrown;
            this.butGen.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butGen.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butGen.Location = new System.Drawing.Point(236, 350);
            this.butGen.Margin = new System.Windows.Forms.Padding(4);
            this.butGen.Name = "butGen";
            this.butGen.Size = new System.Drawing.Size(112, 31);
            this.butGen.TabIndex = 11;
            this.butGen.Text = "Display";
            this.butGen.UseVisualStyleBackColor = false;
            this.butGen.Click += new System.EventHandler(this.butGen_Click);
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblStatus.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.lblStatus.Location = new System.Drawing.Point(202, 168);
            this.lblStatus.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(99, 20);
            this.lblStatus.TabIndex = 4;
            this.lblStatus.Text = "Disconnect";
            // 
            // dataView
            // 
            this.dataView.BackgroundColor = System.Drawing.Color.White;
            this.dataView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataView.GridColor = System.Drawing.Color.White;
            this.dataView.Location = new System.Drawing.Point(420, 33);
            this.dataView.Margin = new System.Windows.Forms.Padding(4);
            this.dataView.Name = "dataView";
            this.dataView.Size = new System.Drawing.Size(419, 210);
            this.dataView.TabIndex = 6;
            this.dataView.RowEnter += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataView_RowEnter);
            // 
            // butConnect
            // 
            this.butConnect.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.butConnect.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butConnect.Location = new System.Drawing.Point(141, 229);
            this.butConnect.Margin = new System.Windows.Forms.Padding(4);
            this.butConnect.Name = "butConnect";
            this.butConnect.Size = new System.Drawing.Size(125, 38);
            this.butConnect.TabIndex = 6;
            this.butConnect.Text = "Connect";
            this.butConnect.UseVisualStyleBackColor = false;
            this.butConnect.Click += new System.EventHandler(this.butConnect_Click);
            // 
            // Ser
            // 
            this.Ser.BaudRate = 115200;
            // 
            // txtPassword
            // 
            this.txtPassword.Location = new System.Drawing.Point(201, 122);
            this.txtPassword.Margin = new System.Windows.Forms.Padding(4);
            this.txtPassword.Name = "txtPassword";
            this.txtPassword.Size = new System.Drawing.Size(124, 20);
            this.txtPassword.TabIndex = 20;
            this.txtPassword.Text = "2013";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(50, 126);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 13);
            this.label6.TabIndex = 18;
            this.label6.Text = "Password";
            // 
            // butOpenWorkDir
            // 
            this.butOpenWorkDir.BackColor = System.Drawing.SystemColors.Control;
            this.butOpenWorkDir.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butOpenWorkDir.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butOpenWorkDir.Location = new System.Drawing.Point(296, 32);
            this.butOpenWorkDir.Margin = new System.Windows.Forms.Padding(4);
            this.butOpenWorkDir.Name = "butOpenWorkDir";
            this.butOpenWorkDir.Size = new System.Drawing.Size(84, 31);
            this.butOpenWorkDir.TabIndex = 15;
            this.butOpenWorkDir.Text = "Browse";
            this.butOpenWorkDir.UseVisualStyleBackColor = false;
            this.butOpenWorkDir.Click += new System.EventHandler(this.butOpenWorkDir_Click);
            // 
            // txtWorkDir
            // 
            this.txtWorkDir.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtWorkDir.Location = new System.Drawing.Point(8, 36);
            this.txtWorkDir.Margin = new System.Windows.Forms.Padding(4);
            this.txtWorkDir.Name = "txtWorkDir";
            this.txtWorkDir.Size = new System.Drawing.Size(280, 20);
            this.txtWorkDir.TabIndex = 16;
            // 
            // txtImageFileName
            // 
            this.txtImageFileName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtImageFileName.Location = new System.Drawing.Point(8, 31);
            this.txtImageFileName.Margin = new System.Windows.Forms.Padding(4);
            this.txtImageFileName.Name = "txtImageFileName";
            this.txtImageFileName.Size = new System.Drawing.Size(299, 20);
            this.txtImageFileName.TabIndex = 13;
            this.txtImageFileName.TextChanged += new System.EventHandler(this.txtImageFileName_TextChanged);
            // 
            // butOpenXls
            // 
            this.butOpenXls.BackColor = System.Drawing.SystemColors.Control;
            this.butOpenXls.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butOpenXls.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butOpenXls.Location = new System.Drawing.Point(41, 46);
            this.butOpenXls.Margin = new System.Windows.Forms.Padding(4);
            this.butOpenXls.Name = "butOpenXls";
            this.butOpenXls.Size = new System.Drawing.Size(131, 31);
            this.butOpenXls.TabIndex = 7;
            this.butOpenXls.Text = "Load Script";
            this.butOpenXls.UseVisualStyleBackColor = false;
            this.butOpenXls.Click += new System.EventHandler(this.butOpenXls_Click);
            // 
            // butSaveScript
            // 
            this.butSaveScript.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.butSaveScript.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butSaveScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butSaveScript.Location = new System.Drawing.Point(212, 121);
            this.butSaveScript.Margin = new System.Windows.Forms.Padding(4);
            this.butSaveScript.Name = "butSaveScript";
            this.butSaveScript.Size = new System.Drawing.Size(131, 31);
            this.butSaveScript.TabIndex = 28;
            this.butSaveScript.Text = "Save Script";
            this.butSaveScript.UseVisualStyleBackColor = false;
            this.butSaveScript.Click += new System.EventHandler(this.butSaveScript_Click);
            // 
            // butDeleteScript
            // 
            this.butDeleteScript.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.butDeleteScript.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butDeleteScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butDeleteScript.Location = new System.Drawing.Point(212, 193);
            this.butDeleteScript.Margin = new System.Windows.Forms.Padding(4);
            this.butDeleteScript.Name = "butDeleteScript";
            this.butDeleteScript.Size = new System.Drawing.Size(131, 31);
            this.butDeleteScript.TabIndex = 27;
            this.butDeleteScript.Text = "Delete Script";
            this.butDeleteScript.UseVisualStyleBackColor = false;
            this.butDeleteScript.Click += new System.EventHandler(this.butDeleteScript_Click);
            // 
            // butNewImage
            // 
            this.butNewImage.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.butNewImage.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butNewImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butNewImage.Location = new System.Drawing.Point(41, 193);
            this.butNewImage.Margin = new System.Windows.Forms.Padding(4);
            this.butNewImage.Name = "butNewImage";
            this.butNewImage.Size = new System.Drawing.Size(131, 31);
            this.butNewImage.TabIndex = 26;
            this.butNewImage.Text = "New Image";
            this.butNewImage.UseVisualStyleBackColor = false;
            this.butNewImage.Click += new System.EventHandler(this.butNewImage_Click);
            // 
            // butNewUScript
            // 
            this.butNewUScript.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.butNewUScript.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butNewUScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butNewUScript.Location = new System.Drawing.Point(212, 46);
            this.butNewUScript.Margin = new System.Windows.Forms.Padding(4);
            this.butNewUScript.Name = "butNewUScript";
            this.butNewUScript.Size = new System.Drawing.Size(131, 31);
            this.butNewUScript.TabIndex = 25;
            this.butNewUScript.Text = "New UScript";
            this.butNewUScript.UseVisualStyleBackColor = false;
            this.butNewUScript.Click += new System.EventHandler(this.butNewUScript_Click);
            // 
            // butNewScript
            // 
            this.butNewScript.BackColor = System.Drawing.Color.PaleGoldenrod;
            this.butNewScript.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butNewScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butNewScript.Location = new System.Drawing.Point(41, 121);
            this.butNewScript.Margin = new System.Windows.Forms.Padding(4);
            this.butNewScript.Name = "butNewScript";
            this.butNewScript.Size = new System.Drawing.Size(131, 31);
            this.butNewScript.TabIndex = 24;
            this.butNewScript.Text = "New Script";
            this.butNewScript.UseVisualStyleBackColor = false;
            this.butNewScript.Click += new System.EventHandler(this.butNewScript_Click);
            // 
            // Tim100ms
            // 
            this.Tim100ms.Enabled = true;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Gray;
            this.panel1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel1.Controls.Add(this.picBox);
            this.panel1.Controls.Add(this.pnGrid);
            this.panel1.Location = new System.Drawing.Point(416, 31);
            this.panel1.Margin = new System.Windows.Forms.Padding(4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(645, 627);
            this.panel1.TabIndex = 3;
            // 
            // picBox
            // 
            this.picBox.BackColor = System.Drawing.Color.White;
            this.picBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.picBox.Location = new System.Drawing.Point(431, 2);
            this.picBox.Margin = new System.Windows.Forms.Padding(4);
            this.picBox.Name = "picBox";
            this.picBox.Size = new System.Drawing.Size(210, 210);
            this.picBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picBox.TabIndex = 0;
            this.picBox.TabStop = false;
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabConnect);
            this.tabControl2.Controls.Add(this.tabSend1Picture);
            this.tabControl2.Controls.Add(this.tabCreatScript);
            this.tabControl2.Controls.Add(this.tabData1Picture);
            this.tabControl2.Controls.Add(this.tabAbout);
            this.tabControl2.Location = new System.Drawing.Point(4, 8);
            this.tabControl2.Margin = new System.Windows.Forms.Padding(4);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(412, 650);
            this.tabControl2.TabIndex = 24;
            // 
            // tabConnect
            // 
            this.tabConnect.BackColor = System.Drawing.Color.DarkTurquoise;
            this.tabConnect.Controls.Add(this.groupBox8);
            this.tabConnect.Controls.Add(this.groupBox7);
            this.tabConnect.Location = new System.Drawing.Point(4, 22);
            this.tabConnect.Margin = new System.Windows.Forms.Padding(4);
            this.tabConnect.Name = "tabConnect";
            this.tabConnect.Padding = new System.Windows.Forms.Padding(4);
            this.tabConnect.Size = new System.Drawing.Size(404, 624);
            this.tabConnect.TabIndex = 2;
            this.tabConnect.Text = "Connect";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.textBox1);
            this.groupBox8.Controls.Add(this.label9);
            this.groupBox8.Controls.Add(this.butLogin);
            this.groupBox8.Controls.Add(this.txtPassword);
            this.groupBox8.Controls.Add(this.label6);
            this.groupBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox8.Location = new System.Drawing.Point(8, 364);
            this.groupBox8.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox8.Size = new System.Drawing.Size(388, 256);
            this.groupBox8.TabIndex = 35;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Login";
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.Location = new System.Drawing.Point(201, 62);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(124, 20);
            this.textBox1.TabIndex = 28;
            this.textBox1.Text = "admin";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(50, 66);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(55, 13);
            this.label9.TabIndex = 27;
            this.label9.Text = "Username";
            // 
            // butLogin
            // 
            this.butLogin.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butLogin.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butLogin.Location = new System.Drawing.Point(141, 185);
            this.butLogin.Margin = new System.Windows.Forms.Padding(4);
            this.butLogin.Name = "butLogin";
            this.butLogin.Size = new System.Drawing.Size(125, 38);
            this.butLogin.TabIndex = 25;
            this.butLogin.Text = "Login";
            this.butLogin.UseVisualStyleBackColor = true;
            this.butLogin.Click += new System.EventHandler(this.butLogin_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label18);
            this.groupBox7.Controls.Add(this.CbBaudRate);
            this.groupBox7.Controls.Add(this.lblStatus);
            this.groupBox7.Controls.Add(this.butConnect);
            this.groupBox7.Controls.Add(this.label4);
            this.groupBox7.Controls.Add(this.label5);
            this.groupBox7.Controls.Add(this.CbSecCom);
            this.groupBox7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox7.Location = new System.Drawing.Point(8, 26);
            this.groupBox7.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox7.Size = new System.Drawing.Size(388, 302);
            this.groupBox7.TabIndex = 34;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Serial Port";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.Location = new System.Drawing.Point(50, 174);
            this.label18.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(40, 13);
            this.label18.TabIndex = 26;
            this.label18.Text = "Status:";
            // 
            // CbBaudRate
            // 
            this.CbBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbBaudRate.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.CbBaudRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CbBaudRate.FormattingEnabled = true;
            this.CbBaudRate.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "56000",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.CbBaudRate.Location = new System.Drawing.Point(201, 109);
            this.CbBaudRate.Margin = new System.Windows.Forms.Padding(4);
            this.CbBaudRate.Name = "CbBaudRate";
            this.CbBaudRate.Size = new System.Drawing.Size(124, 24);
            this.CbBaudRate.TabIndex = 24;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(50, 115);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(32, 13);
            this.label4.TabIndex = 23;
            this.label4.Text = "Baud";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(50, 54);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(26, 13);
            this.label5.TabIndex = 21;
            this.label5.Text = "Port";
            // 
            // CbSecCom
            // 
            this.CbSecCom.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbSecCom.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.CbSecCom.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CbSecCom.FormattingEnabled = true;
            this.CbSecCom.Location = new System.Drawing.Point(201, 48);
            this.CbSecCom.Margin = new System.Windows.Forms.Padding(4);
            this.CbSecCom.Name = "CbSecCom";
            this.CbSecCom.Size = new System.Drawing.Size(124, 24);
            this.CbSecCom.TabIndex = 22;
            // 
            // tabSend1Picture
            // 
            this.tabSend1Picture.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.tabSend1Picture.Controls.Add(this.groupBox2);
            this.tabSend1Picture.Controls.Add(this.groupBox1);
            this.tabSend1Picture.Location = new System.Drawing.Point(4, 22);
            this.tabSend1Picture.Margin = new System.Windows.Forms.Padding(4);
            this.tabSend1Picture.Name = "tabSend1Picture";
            this.tabSend1Picture.Padding = new System.Windows.Forms.Padding(4);
            this.tabSend1Picture.Size = new System.Drawing.Size(404, 624);
            this.tabSend1Picture.TabIndex = 0;
            this.tabSend1Picture.Text = "Image ";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.ckbLoadImg);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.ckbReverseImage);
            this.groupBox2.Controls.Add(this.bt_SendImage);
            this.groupBox2.Controls.Add(this.ckbNegative);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.numWidth);
            this.groupBox2.Controls.Add(this.butGen);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.slider);
            this.groupBox2.Controls.Add(this.numHeight);
            this.groupBox2.Controls.Add(this.lblSlider);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(8, 134);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox2.Size = new System.Drawing.Size(388, 492);
            this.groupBox2.TabIndex = 17;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Setup Display";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 276);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(64, 13);
            this.label8.TabIndex = 21;
            this.label8.Text = "Properties";
            // 
            // ckbLoadImg
            // 
            this.ckbLoadImg.AutoSize = true;
            this.ckbLoadImg.Location = new System.Drawing.Point(35, 382);
            this.ckbLoadImg.Margin = new System.Windows.Forms.Padding(4);
            this.ckbLoadImg.Name = "ckbLoadImg";
            this.ckbLoadImg.Size = new System.Drawing.Size(92, 17);
            this.ckbLoadImg.TabIndex = 19;
            this.ckbLoadImg.Text = "Load Image";
            this.ckbLoadImg.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 50);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(67, 13);
            this.label7.TabIndex = 20;
            this.label7.Text = "Resolution";
            // 
            // ckbReverseImage
            // 
            this.ckbReverseImage.AutoSize = true;
            this.ckbReverseImage.Location = new System.Drawing.Point(35, 420);
            this.ckbReverseImage.Margin = new System.Windows.Forms.Padding(4);
            this.ckbReverseImage.Name = "ckbReverseImage";
            this.ckbReverseImage.Size = new System.Drawing.Size(111, 17);
            this.ckbReverseImage.TabIndex = 11;
            this.ckbReverseImage.Text = "Reverse Image";
            this.ckbReverseImage.UseVisualStyleBackColor = true;
            // 
            // bt_SendImage
            // 
            this.bt_SendImage.BackColor = System.Drawing.Color.SandyBrown;
            this.bt_SendImage.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.bt_SendImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_SendImage.Location = new System.Drawing.Point(236, 408);
            this.bt_SendImage.Margin = new System.Windows.Forms.Padding(4);
            this.bt_SendImage.Name = "bt_SendImage";
            this.bt_SendImage.Size = new System.Drawing.Size(112, 31);
            this.bt_SendImage.TabIndex = 19;
            this.bt_SendImage.Text = "Send";
            this.bt_SendImage.UseVisualStyleBackColor = false;
            this.bt_SendImage.Click += new System.EventHandler(this.bt_SendImage_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.butOpen);
            this.groupBox1.Controls.Add(this.txtImageFileName);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(8, 26);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(388, 81);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Source";
            // 
            // tabCreatScript
            // 
            this.tabCreatScript.BackColor = System.Drawing.Color.LightGreen;
            this.tabCreatScript.Controls.Add(this.groupBox9);
            this.tabCreatScript.Controls.Add(this.groupBox6);
            this.tabCreatScript.Controls.Add(this.groupBox4);
            this.tabCreatScript.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabCreatScript.Location = new System.Drawing.Point(4, 22);
            this.tabCreatScript.Margin = new System.Windows.Forms.Padding(4);
            this.tabCreatScript.Name = "tabCreatScript";
            this.tabCreatScript.Padding = new System.Windows.Forms.Padding(4);
            this.tabCreatScript.Size = new System.Drawing.Size(404, 624);
            this.tabCreatScript.TabIndex = 1;
            this.tabCreatScript.Text = "Script";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.butDownload);
            this.groupBox9.Controls.Add(this.ckbDownloadSpt);
            this.groupBox9.Controls.Add(this.ckbDownloadImg);
            this.groupBox9.Controls.Add(this.ckbCalibrateMem);
            this.groupBox9.Location = new System.Drawing.Point(8, 416);
            this.groupBox9.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox9.Size = new System.Drawing.Size(388, 216);
            this.groupBox9.TabIndex = 34;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Download";
            // 
            // butDownload
            // 
            this.butDownload.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.butDownload.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.butDownload.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.butDownload.Location = new System.Drawing.Point(231, 96);
            this.butDownload.Margin = new System.Windows.Forms.Padding(4);
            this.butDownload.Name = "butDownload";
            this.butDownload.Size = new System.Drawing.Size(131, 31);
            this.butDownload.TabIndex = 22;
            this.butDownload.Text = "Download";
            this.butDownload.UseVisualStyleBackColor = false;
            this.butDownload.Click += new System.EventHandler(this.butDownload_Click);
            // 
            // ckbDownloadSpt
            // 
            this.ckbDownloadSpt.AutoSize = true;
            this.ckbDownloadSpt.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ckbDownloadSpt.Location = new System.Drawing.Point(25, 100);
            this.ckbDownloadSpt.Margin = new System.Windows.Forms.Padding(4);
            this.ckbDownloadSpt.Name = "ckbDownloadSpt";
            this.ckbDownloadSpt.Size = new System.Drawing.Size(116, 19);
            this.ckbDownloadSpt.TabIndex = 32;
            this.ckbDownloadSpt.Text = "Download Script";
            this.ckbDownloadSpt.UseVisualStyleBackColor = true;
            // 
            // ckbDownloadImg
            // 
            this.ckbDownloadImg.AutoSize = true;
            this.ckbDownloadImg.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ckbDownloadImg.Location = new System.Drawing.Point(25, 152);
            this.ckbDownloadImg.Margin = new System.Windows.Forms.Padding(4);
            this.ckbDownloadImg.Name = "ckbDownloadImg";
            this.ckbDownloadImg.Size = new System.Drawing.Size(120, 19);
            this.ckbDownloadImg.TabIndex = 33;
            this.ckbDownloadImg.Text = "Download Image";
            this.ckbDownloadImg.UseVisualStyleBackColor = true;
            // 
            // ckbCalibrateMem
            // 
            this.ckbCalibrateMem.AutoSize = true;
            this.ckbCalibrateMem.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ckbCalibrateMem.Location = new System.Drawing.Point(25, 46);
            this.ckbCalibrateMem.Margin = new System.Windows.Forms.Padding(4);
            this.ckbCalibrateMem.Name = "ckbCalibrateMem";
            this.ckbCalibrateMem.Size = new System.Drawing.Size(123, 19);
            this.ckbCalibrateMem.TabIndex = 30;
            this.ckbCalibrateMem.Text = "Calibrate Memory";
            this.ckbCalibrateMem.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.butOpenWorkDir);
            this.groupBox6.Controls.Add(this.txtWorkDir);
            this.groupBox6.Location = new System.Drawing.Point(8, 26);
            this.groupBox6.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox6.Size = new System.Drawing.Size(388, 89);
            this.groupBox6.TabIndex = 31;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Script";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.butOpenXls);
            this.groupBox4.Controls.Add(this.butSaveScript);
            this.groupBox4.Controls.Add(this.butDeleteScript);
            this.groupBox4.Controls.Add(this.butNewScript);
            this.groupBox4.Controls.Add(this.butNewUScript);
            this.groupBox4.Controls.Add(this.butNewImage);
            this.groupBox4.Location = new System.Drawing.Point(8, 138);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox4.Size = new System.Drawing.Size(388, 251);
            this.groupBox4.TabIndex = 29;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Setup";
            // 
            // tabData1Picture
            // 
            this.tabData1Picture.Controls.Add(this.rtxtGen);
            this.tabData1Picture.Location = new System.Drawing.Point(4, 22);
            this.tabData1Picture.Margin = new System.Windows.Forms.Padding(4);
            this.tabData1Picture.Name = "tabData1Picture";
            this.tabData1Picture.Padding = new System.Windows.Forms.Padding(4);
            this.tabData1Picture.Size = new System.Drawing.Size(404, 624);
            this.tabData1Picture.TabIndex = 3;
            this.tabData1Picture.Text = "Log";
            this.tabData1Picture.UseVisualStyleBackColor = true;
            // 
            // rtxtGen
            // 
            this.rtxtGen.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtxtGen.Location = new System.Drawing.Point(4, 4);
            this.rtxtGen.Margin = new System.Windows.Forms.Padding(4);
            this.rtxtGen.Name = "rtxtGen";
            this.rtxtGen.Size = new System.Drawing.Size(396, 616);
            this.rtxtGen.TabIndex = 0;
            this.rtxtGen.Text = "";
            // 
            // tabAbout
            // 
            this.tabAbout.BackColor = System.Drawing.Color.LightGray;
            this.tabAbout.Controls.Add(this.textBoxDescription);
            this.tabAbout.Controls.Add(this.label12);
            this.tabAbout.Controls.Add(this.logoPictureBox);
            this.tabAbout.Location = new System.Drawing.Point(4, 22);
            this.tabAbout.Margin = new System.Windows.Forms.Padding(4);
            this.tabAbout.Name = "tabAbout";
            this.tabAbout.Padding = new System.Windows.Forms.Padding(4);
            this.tabAbout.Size = new System.Drawing.Size(404, 624);
            this.tabAbout.TabIndex = 4;
            this.tabAbout.Text = "About";
            // 
            // textBoxDescription
            // 
            this.textBoxDescription.Location = new System.Drawing.Point(5, 218);
            this.textBoxDescription.Margin = new System.Windows.Forms.Padding(8, 4, 4, 4);
            this.textBoxDescription.Multiline = true;
            this.textBoxDescription.Name = "textBoxDescription";
            this.textBoxDescription.ReadOnly = true;
            this.textBoxDescription.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxDescription.Size = new System.Drawing.Size(389, 423);
            this.textBoxDescription.TabIndex = 24;
            this.textBoxDescription.TabStop = false;
            this.textBoxDescription.Text = "Chưa nghĩ ra";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(200, 22);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(143, 169);
            this.label12.TabIndex = 14;
            this.label12.Text = resources.GetString("label12.Text");
            // 
            // logoPictureBox
            // 
            this.logoPictureBox.Image = ((System.Drawing.Image)(resources.GetObject("logoPictureBox.Image")));
            this.logoPictureBox.Location = new System.Drawing.Point(5, 22);
            this.logoPictureBox.Margin = new System.Windows.Forms.Padding(4);
            this.logoPictureBox.Name = "logoPictureBox";
            this.logoPictureBox.Size = new System.Drawing.Size(188, 188);
            this.logoPictureBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.logoPictureBox.TabIndex = 13;
            this.logoPictureBox.TabStop = false;
            // 
            // SerTimer
            // 
            this.SerTimer.Enabled = true;
            this.SerTimer.Interval = 500;
            this.SerTimer.Tick += new System.EventHandler(this.SerTimer_Tick);
            // 
            // MainForm
            // 
            this.AllowDrop = true;
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Inherit;
            this.BackColor = System.Drawing.Color.SkyBlue;
            this.ClientSize = new System.Drawing.Size(1582, 655);
            this.Controls.Add(this.tabControl2);
            this.Controls.Add(this.dataView);
            this.Controls.Add(this.panel1);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "MainForm";
            this.Text = "Digital Water Curtain";
            this.Load += new System.EventHandler(this.MainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.slider)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataView)).EndInit();
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picBox)).EndInit();
            this.tabControl2.ResumeLayout(false);
            this.tabConnect.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.tabSend1Picture.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabCreatScript.ResumeLayout(false);
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.tabData1Picture.ResumeLayout(false);
            this.tabAbout.ResumeLayout(false);
            this.tabAbout.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.logoPictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox picBox;
        private System.Windows.Forms.Button butOpen;
        private System.Windows.Forms.Panel pnGrid;
        private System.Windows.Forms.TrackBar slider;
        private System.Windows.Forms.Label lblSlider;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numWidth;
        private System.Windows.Forms.NumericUpDown numHeight;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox ckbNegative;
        private System.Windows.Forms.Button butGen;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.DataGridView dataView;
        private System.IO.Ports.SerialPort Ser;
        private System.Windows.Forms.Button butConnect;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtPassword;
        private System.Windows.Forms.TextBox txtImageFileName;
        private System.Windows.Forms.Timer Tim100ms;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabSend1Picture;
        private System.Windows.Forms.TabPage tabCreatScript;
        private System.Windows.Forms.Button butOpenWorkDir;
        private System.Windows.Forms.TextBox txtWorkDir;
        private System.Windows.Forms.Button butOpenXls;
        private System.Windows.Forms.Button butNewUScript;
        private System.Windows.Forms.Button butNewScript;
        private System.Windows.Forms.Button butNewImage;
        private System.Windows.Forms.Button butDeleteScript;
        private System.Windows.Forms.Button butSaveScript;
        private System.Windows.Forms.ComboBox CbBaudRate;
        private System.Windows.Forms.Label label4;
        public System.Windows.Forms.ComboBox CbSecCom;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Timer SerTimer;
        private System.Windows.Forms.Button butLogin;
        private System.Windows.Forms.TabPage tabConnect;
        private System.Windows.Forms.TabPage tabData1Picture;
        private System.Windows.Forms.RichTextBox rtxtGen;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.CheckBox ckbDownloadImg;
        private System.Windows.Forms.CheckBox ckbDownloadSpt;
        private System.Windows.Forms.CheckBox ckbCalibrateMem;
        private System.Windows.Forms.Button butDownload;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.CheckBox ckbReverseImage;
        private System.Windows.Forms.CheckBox ckbLoadImg;
        private System.Windows.Forms.Button bt_SendImage;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TabPage tabAbout;
        private System.Windows.Forms.TextBox textBoxDescription;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.PictureBox logoPictureBox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label9;
    }
}

