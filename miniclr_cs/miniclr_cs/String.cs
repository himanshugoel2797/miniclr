using System;

namespace System
{
	public class String
	{
		public const String Empty = "";

		public static String Format(string fmt, params object[] vals){
			return fmt;
		}

		public static String Concat(params string[] a){
			return "";
		}

		public int Length {get;}

		public char this [int idx] {
			get{
				return '0';
			}
		}
	}
}

