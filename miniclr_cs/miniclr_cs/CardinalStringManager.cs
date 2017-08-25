using System;

namespace System
{
	enum CardinalStringNames {
		ExceptionDefaultMessage,
		ArgumentExceptionDefaultMessage,
		TypeNotArrayMessage,
	}

	static class CardinalStringManager
	{
		private static string[] us_strs = new string[] {
			"An unhandled exception was thrown.",
			"An invalid argument was specified.",
			"The current System.Type is not an array.",
		};

		public static string GetString(CardinalStringNames name){
			return us_strs[(int)name];
		}
	}
}

