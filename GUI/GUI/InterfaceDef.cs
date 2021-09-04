using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace InterfaceDef
{

    #region Interface to communicate between main form and Uart setting form
    /// <summary>
    /// Methods, which is defined in this interface, must be implemented 
    /// in each object that uses them
    /// </summary>
    public struct Comm
    {
        public string name;
        public int baudrate;
    }
    public interface ICommSetting
    {
        Comm Port { get; set; }
    }
    #endregion

    #region Interface to communicate between main form and Field setting form
    /// <summary>
    /// Methods, which is defined in this interface, must be implemented 
    /// in each object that uses them
    /// </summary>
    public struct Field
    {
        public int col;
        public int row;
        public double dx; // column to column
        public double dy; // row to row
    }
    public interface IFieldSetting
    {
        Field Grid{ get; set; }
    }
    #endregion

    #region Interface to communicate between main form and Map display form
    /// <summary>
    /// Methods, which is defined in this interface, must be implemented 
    /// in each object that uses them
    /// </summary>
    public struct Map
    {
        public double x;
        public double y;
    }
    public interface IMapDisplay
    {
        Map Current { set; get; }
        Map Next { set; get; }
    }
    #endregion

}




