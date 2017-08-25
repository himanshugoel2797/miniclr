using System;
using System.Runtime.CompilerServices;
using System.Reflection;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public abstract class Delegate : ICloneable
	{
		//TODO: review permissions

		public MethodInfo Method {get;}

		public object Target {get;}

		#region ICloneable implementation

		public virtual object Clone ()
		{
			throw new NotImplementedException ();
		}

		#endregion

		public static Delegate Combine(Delegate a, Delegate b){
			throw new NotImplementedException();
		}

		public static Delegate Combine(Delegate[] delegates){
			throw new NotImplementedException();
		}

		public static Delegate CreateDelegate(Type type, object target, string method){
			throw new NotImplementedException();
		}

		public static Delegate CreateDelegate(Type type, Type target, string method){
			throw new NotImplementedException();
		}

		public static Delegate CreateDelegate(Type type, MethodInfo method){
			throw new NotImplementedException();
		}

		public static Delegate Remove(Delegate source, Delegate value){
			throw new NotImplementedException ();
		}

		public static Delegate RemoveAll(Delegate source, Delegate value) {
			throw new NotImplementedException ();
		}

		public object DynamicInvoke(object[] args){
			throw new NotImplementedException ();
		}

		public override bool Equals (object obj)
		{
			return base.Equals (obj);
		}

		public override int GetHashCode ()
		{
			return base.GetHashCode ();
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		extern public virtual Delegate[] GetInvocationList();


		public static bool operator ==(Delegate a, Delegate b){
			return a.Equals (b);
		}

		public static bool operator !=(Delegate a, Delegate b){
			return !a.Equals (b);
		}


	}
}

