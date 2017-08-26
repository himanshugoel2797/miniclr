using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyTitle : Attribute
	{
		public string Title { get;}

		public AssemblyTitle (string title)
		{
			Title = title;
		}
	}
}

