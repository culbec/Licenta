namespace CSharp.encoder;

public class CircularEncoding : Encoder
{
    private const int DEFAULT_CIRCULAR_ENCODING_LENGTH = 3;
    private readonly int length;

    public CircularEncoding()
    {
        this.length = DEFAULT_CIRCULAR_ENCODING_LENGTH;
    }

    public CircularEncoding(int length)
    {
        this.length = length > 2 ? length : DEFAULT_CIRCULAR_ENCODING_LENGTH;
    }

    public override string encode(string m)
    {
        string result = "";

        for (var i = 0; i < m.Length; i++)
        {
            result += m[(i + length) % m.Length];
        }

        return result;
    }
}