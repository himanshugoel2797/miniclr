using System;

namespace System.Reflection
{
	[AttributeUsage(AttributeTargets.Assembly, AllowMultiple = false, Inherited = false)]
	public sealed class AssemblyCulture : Attribute
	{
		public string Culture {get;}

		public AssemblyCulture (string culture)
		{
			Culture = culture;
		}
	}
}

