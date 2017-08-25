using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public abstract class Enum : ValueType, IComparable, IFormattable
	{
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

		//TODO Finish implementing
	}
}

