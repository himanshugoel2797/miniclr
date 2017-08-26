using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyCopyright : Attribute
	{
		public string Copyright {get;}

		public AssemblyCopyright (string copyright)
		{
			Copyright = copyright;
		}
	}
}

