using System;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.ComponentModel;
using System.Collections;
using System.Text;

public class LED_CUBE_Effect : INotifyPropertyChanged
{
    private byte[] _columns = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    public byte[] columns { get { return _columns; } set { _columns = value; } }
    private byte _rows = 0xFF;
    public byte rows { get { return _rows; } set { _rows = value; } }
    private byte _delay = 6;
    public byte delay { get { return _delay; } set { _delay = value; } }
    private string _name = "effect";
    public string name { get { return _name; } set { _name = value; } }

    public LED_CUBE_Effect Clone()
    {
        LED_CUBE_Effect obj = new LED_CUBE_Effect();

        obj.columns = this.columns;
        obj.rows = this.rows;
        obj.delay = this.delay;
        obj.name = this.name;

        return obj;
    }

    public static int Size()
    {
        return 30;
    }

    public bool chk1
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[0];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[0] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk2
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[1];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[1] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk3
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[2];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[2] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk4
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[3];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[3] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk5
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[4];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[4] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk6
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[5];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[5] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk7
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[6];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[6] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public bool chk8
    {
        get
        {
            BitArray bits = new BitArray(new byte[] { rows });
            return bits[7];
        }
        set
        {
            BitArray bits = new BitArray(new byte[] { rows });
            bits[7] = value;
            byte[] retvalue = new byte[1];
            bits.CopyTo(retvalue, 0);
            rows = retvalue[0];
            this.NotifyPropertyChanged("rows");
        }
    }

    public byte delayValue
    {
        get
        { 
            return delay; 
        }
        set
        {
            delay = (byte)value;
            this.NotifyPropertyChanged("delay");
        }
    }

    public LED_CUBE_Effect()
	{

	}

    public LED_CUBE_Effect(byte[] bytes)
    {
        columns = new byte[8];
        Array.Copy(bytes, 0, columns, 0, 8);
        rows = bytes[8];
        delay = bytes[9];
        byte[] ime = new byte[20];
        Array.Copy(bytes, 10, ime, 0, 20);
        name = Encoding.ASCII.GetString(ime);
    }

    public byte[] Bytes()
    {
        MemoryStream ms = new MemoryStream();
        BinaryWriter writeBinay = new BinaryWriter(ms);

        name = (name == null) ? string.Empty : name;
        columns = (columns == null) ? new byte[8] : columns;

        writeBinay.Write(columns);
        writeBinay.Write(rows);
        writeBinay.Write(delay);

        for (int i = 0; i < 20; i++)
        {
            if (i < name.Length)
            {
                writeBinay.Write((char)name[i]);
            }
            else
            {
                writeBinay.Write((char)0x00);
            }
        }

        return ms.ToArray();
    }

    //-- Methods

    private void NotifyPropertyChanged(string propertyName)
    {

        this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));

    }

    //-- Events

    public event PropertyChangedEventHandler PropertyChanged;
}
