using System;

namespace System.Runtime.Versioning
{
	public sealed class TargetFrameworkAttribute : Attribute
	{
		public string FrameworkDisplayName;

		public string Value { get; set;}

		public TargetFrameworkAttribute (string fw_name)
		{
			Value = fw_name;
		}
	}
}

