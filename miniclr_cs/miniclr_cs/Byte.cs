using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public struct Byte : IComparable, IFormattable, IComparable<Byte>, IEquatable<Byte>
	{
		public const byte MaxValue = 255;
		public const byte MinValue = 0;

		#region IEquatable implementation

		public bool Equals (byte obj)
		{
			return this == obj;
		}

		#endregion

		public override bool Equals (object obj)
		{
			if (obj == null)
				return false;

			if (!(obj is bool))
				return false;

			return Equals ((byte)obj);
		}

		#region IComparable implementation

		public int CompareTo (byte o)
		{
			if (this < o)
				return -1;
			else if (this > o)
				return 1;

			return 0;
		}

		#endregion

		#region IComparable implementation
		public int CompareTo (object o)
		{
			if (o == null)
				return 1;

			if (!(o is byte))
				throw new ArgumentException ();

			return CompareTo ((byte)o);
		}
		#endregion

		public override int GetHashCode ()
		{
			return (int)this;
		}

		public string ToString (IFormatProvider provider) {
			return ToString("G", provider);
		}

		public string ToString(string fmt){
			return ToString (fmt, null);
		}

		public override string ToString(){
			return ToString (null, null);
		}

		#region IFormattable implementation

		public string ToString (string format, IFormatProvider formatProvider)
		{
			throw new System.NotImplementedException ();
		}

		#endregion

		public static byte Parse(string s){
			return Parse (s, System.Globalization.NumberStyles.Integer, null);
		}

		public static byte Parse(string s, System.Globalization.NumberStyles style){
			return Parse (s, style, null);
		}

		public static byte Parse(string s, System.IFormatProvider provider){
			return Parse (s, System.Globalization.NumberStyles.Integer, provider);
		}

		public static byte Parse(string s, System.Globalization.NumberStyles style, System.IFormatProvider provider){
			throw new NotImplementedException ();
		}
	}
}

