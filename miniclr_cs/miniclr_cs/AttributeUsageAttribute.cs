using System;

namespace System
{

	[Serializable]
	[CLSCompliant(true)]
	[AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
	public sealed class AttributeUsageAttribute : Attribute
	{
		public bool AllowMultiple {get;set;}
		public bool Inherited {get; set;}
		public AttributeTargets ValidOn { get;}

		public AttributeUsageAttribute (AttributeTargets validOn)
		{
			ValidOn = validOn;
		}
	}
}

