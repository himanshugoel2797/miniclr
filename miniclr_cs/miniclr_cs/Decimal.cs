using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public struct Decimal : IComparable, IFormattable, IComparable<Decimal>, IEquatable<Decimal>
	{
		//TODO: Finish implementation
		#region IEquatable implementation

		public bool Equals (decimal obj)
		{
			throw new NotImplementedException ();
		}

		#endregion

		#region IComparable implementation

		public int CompareTo (decimal o)
		{
			throw new NotImplementedException ();
		}

		#endregion

		#region IFormattable implementation

		public string ToString (string format, IFormatProvider formatProvider)
		{
			throw new NotImplementedException ();
		}

		#endregion

		#region IComparable implementation
		public int CompareTo (object o)
		{
			throw new NotImplementedException ();
		}
		#endregion
	}
}

