using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyVersion : Attribute
	{
		public string Version {get;}

		public AssemblyVersion (string ver)
		{
			Version = ver;
		}
	}
}

