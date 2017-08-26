using System;

namespace System
{
	[AttributeUsage(AttributeTargets.All, AllowMultiple = false, Inherited = true)]
	[CLSCompliant(true)]
	[Serializable]
	public class Attribute
	{
		//TODO: Finish implementation

		protected Attribute ()
		{
		}

		public override bool Equals (object obj)
		{
			return base.Equals (obj);
		}

		public override int GetHashCode ()
		{
			return base.GetHashCode ();
		}

	}
}

