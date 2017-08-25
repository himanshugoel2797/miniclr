using System;
using System.Runtime.CompilerServices;

namespace System
{
	[Serializable]
	public abstract class Type : System.Reflection.MemberInfo
	{
		protected Type ()
		{
		}

		private int ArrayRank = 0;

		public static readonly char Delimiter = '.';
		public static readonly Type[] EmptyTypes;
		public static readonly object Missing;

		[MethodImpl(MethodImplOptions.InternalCall)]
		extern public static Type GetTypeFromHandle(RuntimeTypeHandle handle);

		public readonly string FullName;

		public virtual int GetArrayRank() {
			if (ArrayRank == 0)
				throw new ArgumentException ( CardinalStringManager.GetString(CardinalStringNames.TypeNotArrayMessage) );
			return ArrayRank;
		}
	}
}

