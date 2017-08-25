using System;

namespace System
{
	public struct Int16 : IComparable, IFormattable, IComparable<Int16>, IEquatable<Int16>
	{
		public const short MaxValue = 32767;
		public const short MinValue = -32768;

		#region IEquatable implementation

		public bool Equals (short obj)
		{
			return this == obj;
		}

		#endregion

		public override int GetHashCode ()
		{
			return (int)this;
		}

		public override bool Equals (object obj)
		{
			if (obj == null)
				return false;

			if (!(obj is short))
				return false;

			return Equals ((short)obj);
		}

		#region IComparable implementation

		public int CompareTo (short o)
		{
			return this - o;
		}

		#endregion
		
		#region IComparable implementation
		public int CompareTo (object o)
		{
			if (!(o is short))
				throw new ArgumentException ();

			if (o == null)
				return 1;

			return CompareTo ((short)o);
		}
		#endregion

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

		public static short Parse(string s){
			return Parse (s, System.Globalization.NumberStyles.Integer, null);
		}

		public static short Parse(string s, System.Globalization.NumberStyles style){
			return Parse (s, style, null);
		}

		public static short Parse(string s, System.IFormatProvider provider){
			return Parse (s, System.Globalization.NumberStyles.Integer, provider);
		}

		public static short Parse(string s, System.Globalization.NumberStyles style, System.IFormatProvider provider){
			throw new NotImplementedException ();
		}

	}
}

