using System;

namespace System
{
	public interface IComparable
	{
		int CompareTo(object o);
	}

	public interface IComparable<in T>
	{
		int CompareTo(T o);
	}
}

