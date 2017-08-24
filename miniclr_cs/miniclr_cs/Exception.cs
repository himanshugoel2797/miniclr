using System;

namespace System
{
	public class Exception
	{
		public virtual String Message { get; }
		public virtual String StackTrace { get;}
		public Exception InnerException {get;}

		public Exception () : this(null)
		{
			
		}

		public Exception(string message) : this(message, null)
		{
		}

		public Exception(string message, Exception innerException){

			Message = message;
			if (message == null)
				Message = CardinalStringManager.GetString (CardinalStringNames.ExceptionDefaultMessage);

			InnerException = innerException;
			StackTrace = String.Empty;
		}

		public virtual Exception GetBaseException(){
			if (InnerException == null)
				return this;

			return InnerException.GetBaseException ();
		}

		public override string ToString ()
		{
			return string.Format ("[Exception: Message={0}, StackTrace={1}, InnerException={2}]", Message, StackTrace, InnerException);
		}
	}
}

