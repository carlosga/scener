#ifndef BINARYREADER_HPP
#define BINARYREADER_HPP

namespace System
{
	namespace IO
	{
		// Summary:
		//     Reads primitive data types as binary values in a specific encoding.
		[ComVisible(true)]
		public class BinaryReader : IDisposable
		{
			// Summary:
			//     Initializes a new instance of the System.IO.BinaryReader class based on the
			//     supplied stream and using System.Text.UTF8Encoding.
			//
			// Parameters:
			//   input:
			//     A stream.
			//
			// Exceptions:
			//   System.ArgumentException:
			//     The stream does not support reading, the stream is null, or the stream is
			//     already closed.
			public BinaryReader(Stream input);
			//
			// Summary:
			//     Initializes a new instance of the System.IO.BinaryReader class based on the
			//     supplied stream and a specific character encoding.
			//
			// Parameters:
			//   input:
			//     The supplied stream.
			//
			//   encoding:
			//     The character encoding.
			//
			// Exceptions:
			//   System.ArgumentException:
			//     The stream does not support reading, the stream is null, or the stream is
			//     already closed.
			//
			//   System.ArgumentNullException:
			//     encoding is null.
			public BinaryReader(Stream input, Encoding encoding);

			// Summary:
			//     Exposes access to the underlying stream of the System.IO.BinaryReader.
			//
			// Returns:
			//     The underlying stream associated with the BinaryReader.
			public virtual Stream BaseStream { get; }

			// Summary:
			//     Closes the current reader and the underlying stream.
			public virtual void Close();
			//
			// Summary:
			//     Releases the unmanaged resources used by the System.IO.BinaryReader and optionally
			//     releases the managed resources.
			//
			// Parameters:
			//   disposing:
			//     true to release both managed and unmanaged resources; false to release only
			//     unmanaged resources.
			protected virtual void Dispose(bool disposing);
			//
			// Summary:
			//     Fills the internal buffer with the specified number of bytes read from the
			//     stream.
			//
			// Parameters:
			//   numBytes:
			//     The number of bytes to be read.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached before numBytes could be read.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.ArgumentOutOfRangeException:
			//     Requested numBytes is larger than the internal buffer size.
			protected virtual void FillBuffer(int numBytes);
			//
			// Summary:
			//     Returns the next available character and does not advance the byte or character
			//     position.
			//
			// Returns:
			//     The next available character, or -1 if no more characters are available or
			//     the stream does not support seeking.
			//
			// Exceptions:
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual int PeekChar();
			//
			// Summary:
			//     Reads characters from the underlying stream and advances the current position
			//     of the stream in accordance with the Encoding used and the specific character
			//     being read from the stream.
			//
			// Returns:
			//     The next character from the input stream, or -1 if no characters are currently
			//     available.
			//
			// Exceptions:
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			public virtual int Read();
			//
			// Summary:
			//     Reads count bytes from the stream with index as the starting point in the
			//     byte array.
			//
			// Parameters:
			//   buffer:
			//     The buffer to read data into.
			//
			//   index:
			//     The starting point in the buffer at which to begin reading into the buffer.
			//
			//   count:
			//     The number of characters to read.
			//
			// Returns:
			//     The number of characters read into buffer. This might be less than the number
			//     of bytes requested if that many bytes are not available, or it might be zero
			//     if the end of the stream is reached.
			//
			// Exceptions:
			//   System.ArgumentException:
			//     The buffer length minus index is less than count.
			//
			//   System.ArgumentNullException:
			//     buffer is null.
			//
			//   System.ArgumentOutOfRangeException:
			//     index or count is negative.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual int Read(byte[] buffer, int index, int count);
			//
			// Summary:
			//     Reads count characters from the stream with index as the starting point in
			//     the character array.
			//
			// Parameters:
			//   buffer:
			//     The buffer to read data into.
			//
			//   index:
			//     The starting point in the buffer at which to begin reading into the buffer.
			//
			//   count:
			//     The number of characters to read.
			//
			// Returns:
			//     The total number of characters read into the buffer. This might be less than
			//     the number of characters requested if that many characters are not currently
			//     available, or it might be zero if the end of the stream is reached.
			//
			// Exceptions:
			//   System.ArgumentException:
			//     The buffer length minus index is less than count.
			//
			//   System.ArgumentNullException:
			//     buffer is null.
			//
			//   System.ArgumentOutOfRangeException:
			//     index or count is negative.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual int Read(char[] buffer, int index, int count);
			//
			// Summary:
			//     Reads in a 32-bit integer in compressed format.
			//
			// Returns:
			//     A 32-bit integer in compressed format.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.FormatException:
			//     The stream is corrupted.
			protected internal int Read7BitEncodedInt();
			//
			// Summary:
			//     Reads a Boolean value from the current stream and advances the current position
			//     of the stream by one byte.
			//
			// Returns:
			//     true if the byte is nonzero; otherwise, false.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual bool ReadBoolean();
			//
			// Summary:
			//     Reads the next byte from the current stream and advances the current position
			//     of the stream by one byte.
			//
			// Returns:
			//     The next byte read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual byte ReadByte();
			//
			// Summary:
			//     Reads count bytes from the current stream into a byte array and advances
			//     the current position by count bytes.
			//
			// Parameters:
			//   count:
			//     The number of bytes to read.
			//
			// Returns:
			//     A byte array containing data read from the underlying stream. This might
			//     be less than the number of bytes requested if the end of the stream is reached.
			//
			// Exceptions:
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.ArgumentOutOfRangeException:
			//     count is negative.
			public virtual byte[] ReadBytes(int count);
			//
			// Summary:
			//     Reads the next character from the current stream and advances the current
			//     position of the stream in accordance with the Encoding used and the specific
			//     character being read from the stream.
			//
			// Returns:
			//     A character read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.ArgumentException:
			//     A surrogate character was read.
			public virtual char ReadChar();
			//
			// Summary:
			//     Reads count characters from the current stream, returns the data in a character
			//     array, and advances the current position in accordance with the Encoding
			//     used and the specific character being read from the stream.
			//
			// Parameters:
			//   count:
			//     The number of characters to read.
			//
			// Returns:
			//     A character array containing data read from the underlying stream. This might
			//     be less than the number of characters requested if the end of the stream
			//     is reached.
			//
			// Exceptions:
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.ArgumentOutOfRangeException:
			//     count is negative.
			public virtual char[] ReadChars(int count);
			//
			// Summary:
			//     Reads a decimal value from the current stream and advances the current position
			//     of the stream by sixteen bytes.
			//
			// Returns:
			//     A decimal value read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual decimal ReadDecimal();
			//
			// Summary:
			//     Reads an 8-byte floating point value from the current stream and advances
			//     the current position of the stream by eight bytes.
			//
			// Returns:
			//     An 8-byte floating point value read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual double ReadDouble();
			//
			// Summary:
			//     Reads a 2-byte signed integer from the current stream and advances the current
			//     position of the stream by two bytes.
			//
			// Returns:
			//     A 2-byte signed integer read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual short ReadInt16();
			//
			// Summary:
			//     Reads a 4-byte signed integer from the current stream and advances the current
			//     position of the stream by four bytes.
			//
			// Returns:
			//     A 4-byte signed integer read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual int ReadInt32();
			//
			// Summary:
			//     Reads an 8-byte signed integer from the current stream and advances the current
			//     position of the stream by eight bytes.
			//
			// Returns:
			//     An 8-byte signed integer read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual long ReadInt64();
			//
			// Summary:
			//     Reads a signed byte from this stream and advances the current position of
			//     the stream by one byte.
			//
			// Returns:
			//     A signed byte read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			[CLSCompliant(false)]
			public virtual sbyte ReadSByte();
			//
			// Summary:
			//     Reads a 4-byte floating point value from the current stream and advances
			//     the current position of the stream by four bytes.
			//
			// Returns:
			//     A 4-byte floating point value read from the current stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual float ReadSingle();
			//
			// Summary:
			//     Reads a string from the current stream. The string is prefixed with the length,
			//     encoded as an integer seven bits at a time.
			//
			// Returns:
			//     The string being read.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			public virtual string ReadString();
			//
			// Summary:
			//     Reads a 2-byte unsigned integer from the current stream using little-endian
			//     encoding and advances the position of the stream by two bytes.
			//
			// Returns:
			//     A 2-byte unsigned integer read from this stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			[CLSCompliant(false)]
			public virtual ushort ReadUInt16();
			//
			// Summary:
			//     Reads a 4-byte unsigned integer from the current stream and advances the
			//     position of the stream by four bytes.
			//
			// Returns:
			//     A 4-byte unsigned integer read from this stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			[CLSCompliant(false)]
			public virtual uint ReadUInt32();
			//
			// Summary:
			//     Reads an 8-byte unsigned integer from the current stream and advances the
			//     position of the stream by eight bytes.
			//
			// Returns:
			//     An 8-byte unsigned integer read from this stream.
			//
			// Exceptions:
			//   System.IO.EndOfStreamException:
			//     The end of the stream is reached.
			//
			//   System.IO.IOException:
			//     An I/O error occurs.
			//
			//   System.ObjectDisposedException:
			//     The stream is closed.
			[CLSCompliant(false)]
			public virtual ulong ReadUInt64();
		}
	}
}

#endif BINARYREADER_HPP