using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyCompany : Attribute
	{
		public string Company {get;}

		public AssemblyCompany (string company)
		{
			Company = company;
		}
	}
}

