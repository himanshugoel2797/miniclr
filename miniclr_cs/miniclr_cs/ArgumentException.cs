using System;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public class ArgumentException : SystemException
	{
		//public override string Message { get; }
		public virtual string ParamName {get; }

		public ArgumentException () : this(CardinalStringManager.GetString(CardinalStringNames.ArgumentExceptionDefaultMessage)){
			
		}

		public ArgumentException (string message) : this(message, (Exception)null)
		{
		}

		public ArgumentException (string message, Exception innerException) : this(message, null, innerException){
		}

		public ArgumentException (string message, string paramName) : this(message, paramName, null)
		{
		}

		public ArgumentException (string message, string paramName, Exception innerException) : base(message + " " + paramName, innerException){
			ParamName = paramName;
		}
	}
}

