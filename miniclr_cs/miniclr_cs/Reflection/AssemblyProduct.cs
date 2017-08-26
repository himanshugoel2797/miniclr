using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyProduct : Attribute
	{
		public string Product {get;}

		public AssemblyProduct (string product)
		{
			Product = product;
		}
	}
}

