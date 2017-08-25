using System;

namespace System.Runtime.CompilerServices
{
	[Serializable]
	[CLSCompliant(true)]
	[AttributeUsage(AttributeTargets.Constructor | AttributeTargets.Method, AllowMultiple = false, Inherited = false)]
	public sealed class MethodImplAttribute : Attribute
	{
		public MethodImplOptions Value { get; }

		public MethodImplAttribute(){}

		public MethodImplAttribute (MethodImplOptions methodImplOptions)
		{
			Value = methodImplOptions;
		}

		public MethodImplAttribute(short s) : this((MethodImplOptions)s){ 

		}

	}
}

