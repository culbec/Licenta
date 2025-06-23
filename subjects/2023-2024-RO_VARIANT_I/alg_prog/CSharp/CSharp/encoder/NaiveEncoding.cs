namespace CSharp.encoder;

public class NaiveEncoding : Encoder
{

    public override string encode(string m)
    {
        string result = "";

        for (var i = m.Length - 1; i >= 0; i--)
        {
            result += m[i];
        }

        return result;
    }
}