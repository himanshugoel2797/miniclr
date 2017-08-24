using System;

namespace System.Globalization
{
	[Flags]
	public enum NumberStyles
	{
		None = 0x0,
		AllowLeadingWhite = 0x1,
		AllowTrailingWhite = 0x2,
		AllowLeadingSign = 0x4,
		AllowTrailingSign = 0x8,
		AllowParentheses = 0x10,
		AllowDecimalPoint = 0x20,
		AllowThousands = 0x40,
		AllowExponent = 0x80,
		AllowCurrencySymbol = 0x100,
		AllowHexSpecifier = 0x200,

		Any = (AllowLeadingWhite | AllowTrailingWhite | AllowLeadingSign | AllowTrailingSign | AllowParentheses | AllowDecimalPoint | AllowThousands | AllowExponent | AllowCurrencySymbol),
		Currency = (AllowLeadingWhite | AllowTrailingWhite | AllowLeadingSign | AllowTrailingSign | AllowParentheses | AllowDecimalPoint | AllowThousands | AllowCurrencySymbol),
		Float = (AllowLeadingWhite | AllowTrailingWhite | AllowLeadingSign | AllowDecimalPoint | AllowExponent),
		HexNumber = (AllowLeadingWhite | AllowTrailingWhite | AllowHexSpecifier),
		Integer = (AllowLeadingWhite | AllowTrailingWhite | AllowLeadingSign),
		Number = (AllowLeadingWhite | AllowTrailingWhite | AllowLeadingSign | AllowTrailingSign | AllowDecimalPoint | AllowThousands),
	}
}

