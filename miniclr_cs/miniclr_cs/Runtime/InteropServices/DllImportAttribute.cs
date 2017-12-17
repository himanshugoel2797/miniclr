using System;

namespace System.Runtime.InteropServices
{
	[AttributeUsageAttribute(AttributeTargets.Method, Inherited = false)]
	public sealed class DllImportAttribute : Attribute
	{
		public string Value { get; set;}

		public DllImportAttribute (string s)
		{
			Value = s;
		}
	}
}

