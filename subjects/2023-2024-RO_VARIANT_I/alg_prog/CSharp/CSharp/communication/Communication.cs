namespace CSharp.encoder;

public class Communication
{
    private readonly Encoder code;
    private List<string> encodedMessages = [];

    public Communication(Encoder? e)
    {
        // NaiveEncoding as the default Encoder
        this.code = e ?? new NaiveEncoding();
    }

    public void addMessage(string m)
    {
        this.encodedMessages.Add(code.encode(m));
    }

    public List<string> getEncodedMessages()
    {
        return this.encodedMessages;
    }

    public override string ToString()
    {
        string result = "";

        for (var i = 0; i < this.encodedMessages.Count; i++)
        {
            result += this.encodedMessages[i];
            if (i != this.encodedMessages.Count - 1)
            {
                result += '#';
            }
        }

        return result;
    }
}