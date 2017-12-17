using System;
using System.Collections;

namespace System
{
	[Serializable]
	[CLSCompliant(true)]
	public class Array : ICloneable, IList, ICollection, IEnumerable
	{
		//TODO: Finish implementation

		public int Length {get;private set;}

		#region IList implementation

		public int Add (object value)
		{
			throw new NotImplementedException ();
		}

		public void Clear ()
		{
			throw new NotImplementedException ();
		}

		public bool Contains (object value)
		{
			throw new NotImplementedException ();
		}

		public int IndexOf (object value)
		{
			throw new NotImplementedException ();
		}

		public void Insert (int index, object value)
		{
			throw new NotImplementedException ();
		}

		public void Remove (object value)
		{
			throw new NotImplementedException ();
		}

		public void RemoveAt (int index)
		{
			throw new NotImplementedException ();
		}

		public bool IsFixedSize {
			get {
				throw new NotImplementedException ();
			}
		}

		public bool IsReadOnly {
			get {
				throw new NotImplementedException ();
			}
		}

		public object this [int index] {
			get {
				throw new NotImplementedException ();
			}
			set {
				throw new NotImplementedException ();
			}
		}

		#endregion

		#region ICollection implementation

		public void CopyTo (Array array, int index)
		{
			throw new NotImplementedException ();
		}

		public int Count {
			get {
				throw new NotImplementedException ();
			}
		}

		public bool IsSynchronized {
			get {
				throw new NotImplementedException ();
			}
		}

		public object SyncRoot {
			get {
				throw new NotImplementedException ();
			}
		}

		#endregion

		#region IEnumerable implementation

		public IEnumerator GetEnumerator ()
		{
			throw new NotImplementedException ();
		}

		#endregion

		#region ICloneable implementation

		public object Clone ()
		{
			throw new NotImplementedException ();
		}

		#endregion

		private Array ()
		{
		}
	}
}

