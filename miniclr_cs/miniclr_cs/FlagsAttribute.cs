using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	[AttributeUsage(AttributeTargets.Enum, AllowMultiple = false, Inherited = false)]
	public class FlagsAttribute : Attribute
	{
		public FlagsAttribute ()
		{
		}
	}
}

