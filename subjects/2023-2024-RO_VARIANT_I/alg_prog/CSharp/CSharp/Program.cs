// See https://aka.ms/new-console-template for more information

using CSharp.encoder;

List<string> mergeMessagesRec(List<string> L1, int indexL1, List<string> L2, int indexL2)
{
    if (indexL1 < 0 && indexL2 < 0)
    {
        return [];
    } else if (indexL1 >= 0 && indexL2 < 0)
    {
        var r1 = mergeMessagesRec(L1, indexL1 - 1, L2, indexL2);
        r1.Add(L1[indexL1]);
        return r1;
    } else if (indexL1 < 0 && indexL2 >= 0)
    {
        var r2 = mergeMessagesRec(L1, indexL1, L2, indexL2 - 1);
        r2.Add(L2[indexL2]);
        return r2;
    }

    // as we compare from end to beginning, we add the elements in reverse
    // (first the greater, then the smaller)
    if (string.Compare(L1[indexL1], L2[indexL2], StringComparison.Ordinal) < 0)
    {
        var r3 = mergeMessagesRec(L1, indexL1, L2, indexL2 - 1);
        r3.Add(L2[indexL2]);
        return r3;
    }

    var r4 = mergeMessagesRec(L1, indexL1 - 1, L2, indexL2);
    r4.Add(L1[indexL1]);
    return r4;
}

List<string> mergeMessages(List<string> L1, List<string> L2)
{
    return mergeMessagesRec(L1, L1.Count - 1, L2, L2.Count - 1);
}

bool isCircularPermutation(string m1, string m2)
{
    if (m1.Length != m2.Length)
    {
        return false;
    }

    if (string.Compare(m1, m2, StringComparison.Ordinal) == 0)
    {
        return true;
    }

    var mLength = m1.Length;
    for (var permLength = 1; permLength < mLength; permLength++)
    {
        var ok = true;

        for (var i = 0; i < mLength && ok; i++)
        {
            if (m1[(i + permLength) % mLength] != m2[i])
            {
                ok = false;
            }
        }

        if (ok)
        {
            return true;
        }
    }

    return false;
}

int numberOfUniqueEncodedMessagesOfCommunication(Communication c)
{
    ISet<string> messagesSet = new HashSet<string>();

    c.getEncodedMessages().ForEach(message => { messagesSet.Add(message); });

    return messagesSet.Count;
}

Communication o1 = new Communication(new CircularEncoding(10));
Communication o2 = new Communication(new NaiveEncoding());

o1.addMessage("bac"); o2.addMessage("bac");
o1.addMessage("cod"); o2.addMessage("cod");
o1.addMessage("apt"); o2.addMessage("apt");

List<string> merged_o1_o2 = mergeMessages(o1.getEncodedMessages(), o2.getEncodedMessages());
merged_o1_o2.ForEach(message => Console.Write("{0} ", message));
Console.WriteLine();