namespace System
{
	[SerializableAttribute]
	public class Object
	{
		public Object(){
		}

		~Object(){
		}

		public static bool Equals(Object o1, Object o2) {
			if (o1 == null && o2 == null)
				return true;
			else if (o1 == null && o2 != null)
				return false;
				
			return o1.Equals (o2);
		}

		public static bool ReferenceEquals(Object o1, Object o2) {
			return (o1 == o2);
		}

		public virtual string ToString(){
			return this.GetType ().FullName;
		}

		extern public virtual bool Equals (Object obj);

		//TODO: MethodImpl
		extern public virtual int GetHashCode ();

		extern public Type GetType();

		extern protected object MemberwiseClone();
	}
}

