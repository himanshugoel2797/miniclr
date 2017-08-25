using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public struct Char : IComparable, IComparable<Char>, IEquatable<Char>
	{
		public const char MaxValue = (char)0xFFFF;
		public const char MinValue = (char)0x0000;

		#region IEquatable implementation

		public bool Equals (char obj)
		{
			return this == obj;
		}

		#endregion

		public override bool Equals (object obj)
		{
			if (obj == null)
				return false;

			if (!(obj is char))
				return false;

			return Equals ((char)obj);
		}

		public override int GetHashCode ()
		{
			return (int)this;
		}

		#region IComparable implementation

		public int CompareTo (char o)
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

			if (!(o is char))
				throw new ArgumentException ();

			return CompareTo ((char)o);
		}
		#endregion

		public static double GetNumericValue(string s, int index){
			if (s == null)
				throw new ArgumentNullException ();

			if (index >= s.Length)
				throw new ArgumentOutOfRangeException ();

			return GetNumericValue(s [index]);
		}

		public static double GetNumericValue(char c){
			throw new NotImplementedException ();
		}

		//TODO: Finish implementation


	}
}

