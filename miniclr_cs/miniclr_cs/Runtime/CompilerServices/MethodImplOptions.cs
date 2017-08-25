using System;

namespace System.Runtime.CompilerServices
{
	[Serializable]
	[CLSCompliant(true)]
	public enum MethodImplOptions
	{
		ForwardRef = 16,
		InternalCall = 4096,
		NoInlining = 8,
		Synchronized = 32,
		Unmanaged = 4,
	}
}

