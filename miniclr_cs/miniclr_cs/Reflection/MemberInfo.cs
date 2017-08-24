using System;

namespace System.Reflection
{
	public abstract class MemberInfo
	{
		protected MemberInfo ()
		{
		}

		public abstract Type DeclaringType {get;}
		public abstract Type ReflectedType {get;}

		public abstract String Name {get;}
	}
}

