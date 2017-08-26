using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyConfiguration : Attribute
	{
		public string Configuration { get;}

		public AssemblyConfiguration (string conf)
		{
			Configuration = conf;
		}
	}
}

