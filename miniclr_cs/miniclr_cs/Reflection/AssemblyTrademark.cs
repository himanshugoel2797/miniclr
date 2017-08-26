using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyTrademark : Attribute
	{
		public string Trademark {get;}

		public AssemblyTrademark (string trademark)
		{
			Trademark = trademark;
		}
	}
}

