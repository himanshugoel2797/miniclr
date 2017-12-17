using System;

namespace System.Runtime.InteropServices
{
	[AttributeUsageAttribute(AttributeTargets.Field | AttributeTargets.Parameter | AttributeTargets.ReturnValue, 
		Inherited = false)]
	public sealed class MarshalAsAttribute : Attribute
	{
		public UnmanagedType Value { get; set;}

		public int SizeConst;

		public MarshalAsAttribute (UnmanagedType t)
		{
			Value = t;
		}
	}
}

