using System;

namespace System
{
	public class ArgumentException : Exception
	{
		public override string Message { get; private set;}
		public virtual string ParamName {get;private set;}

		public ArgumentException () : this(CardinalStringManager.GetString(CardinalStringNames.ArgumentExceptionDefaultMessage)){
			
		}

		public ArgumentException (string message) : this(message, null)
		{
		}

		public ArgumentException (string message, Exception innerException) : this(message, null, innerException){
		}

		public ArgumentException (string message, string paramName) : this(message, paramName, null)
		{
		}

		public ArgumentException (string message, string paramName, Exception innerException) : base(message, innerException){
			ParamName = paramName;
			Message = message + " " + paramName;
		}
	}
}

