using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public struct Boolean : IComparable, IComparable<Boolean>, IEquatable<Boolean>
	{
		//TODO: review and finish

		public static readonly string FalseString = "False";
		public static readonly string TrueString = "True";


		#region IComparable implementation

		public int CompareTo (bool o)
		{
			if (!this && o)
				return -1;
			else if (this == o)
				return 0;
			else
				return 1;
		}

		#endregion

		#region IComparable implementation
		public int CompareTo (object o)
		{
			if (o == null)
				return 1;

			if (!(o is bool))
				throw new ArgumentException ();

			return CompareTo ((bool)o);
		}
		#endregion

		#region IEquatable implementation
		
		public bool Equals (bool obj)
		{
			return (obj == this);
		}
		
		#endregion

		public override bool Equals (object obj)
		{
			if (obj == null)
				return false;

			if (!(obj is bool))
				return false;

			return Equals ((Boolean)obj);
		}

		public override int GetHashCode ()
		{
			if (this)
				return 1;
			else
				return 0;
		}


	}
}

