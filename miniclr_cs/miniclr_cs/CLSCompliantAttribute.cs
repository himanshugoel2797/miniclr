using System;

namespace System
{
	[Serializable]
	[AttributeUsage(AttributeTargets.All, AllowMultiple = false, Inherited = true)]
	[CLSCompliant(true)]
	public class CLSCompliantAttribute : Attribute
	{
		public bool IsCompliant {get;}

		public CLSCompliantAttribute (bool isCompliant)
		{
			IsCompliant = isCompliant;
		}
	}
}

