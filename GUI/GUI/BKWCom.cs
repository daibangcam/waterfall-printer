using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

using InterfaceDef;

namespace BKWCom
{
    class BKWCom: System.IO.Ports.SerialPort, ICommSetting
    {
        private System.IO.Ports.SerialPort Ser;
        private Comm port;

        // Constructor
        public BKWCom()
        {
            
        }

        #region Implement the external interface ICommSetting
        public Comm Port
        {
            set
            {
                this.port.name = value.name;
                this.port.baudrate = value.baudrate;
            }
            get
            {
                return this.port;
            }
        }
        #endregion

        public bool ExchangeData(byte[] req, int req_len, byte[] res, int res_len)
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
                    while (tim.ElapsedMilliseconds < 2000)
                    {
                        if (Ser.BytesToRead >= res_len)
                        {
                            // Getting the response frame
                            Ser.Read(res, 0, res_len);
                            if (DiagData(res, 4))
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
                //MessageBox.Show("Port is closed!");
            }
            return ret;
        }

        public bool DiagData(byte[] recv_data, int len)
        {
            bool res = false;
            if ((recv_data[0] == 0x0A) &&
                (recv_data[3] == 0x0D))
            {
                if ((recv_data[1] == (byte)'T') &&
                    (recv_data[2] == (byte)'0'))
                {
                    res = true;
                }
            }
            return res;
        }

        public bool ReadData(byte[] dat, int len)
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
                    //MessageBox.Show("Port is closed or timeout!");
                }
                return res;
            }
            catch
            {
                return res;
            }
        }


    }
}
