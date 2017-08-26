using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyDescription : Attribute
	{
		public string Description { get;}

		public AssemblyDescription (string desc)
		{
			Description = desc;
		}
	}
}

