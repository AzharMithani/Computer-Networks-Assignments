package DNSLookup;
/**
 *
 * @author azhar
 */
import javax.naming.directory.Attributes;
import javax.naming.directory.InitialDirContext;
import javax.naming.NamingEnumeration;
import javax.naming.NamingException;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class DNSLookup
{
    public static void main(String args[])
    {
        if (args.length != 1)
        {
            System.err.println("Print out DNS Record for an Internet Address");
            System.err.println("USAGE: java DNSLookup domainName|domainAddress");
            System.exit(-1);
        }
        try
        {
            InetAddress inetAddress;
            if (Character.isDigit(args[0].charAt(0)))
			{
                byte[] b = new byte[4];
                String[] bytes = args[0].split("[.]");
                for (int i = 0; i < bytes.length; i++)
                {
                    b[i] = new Integer(bytes[i]).byteValue();
                }
                inetAddress = InetAddress.getByAddress(b);
            }
            else
			{
                inetAddress = InetAddress.getByName(args[0]);
            }
            System.out.println(inetAddress.getHostName() + "/" + inetAddress.getHostAddress());
            InitialDirContext iDirC = new InitialDirContext();
            Attributes attributes = iDirC.getAttributes("dns:/" + inetAddress.getHostName());
            NamingEnumeration attributeEnumeration = attributes.getAll();
            System.out.println("-- DNS INFORMATION --");
            while (attributeEnumeration.hasMore())
            {
                System.out.println("" + attributeEnumeration.next());
            }
            attributeEnumeration.close();
        }
        catch (UnknownHostException exception)
        {
            System.err.println("ERROR: No Internet Address for '" + args[0] + "'");
        }
        catch (NamingException exception)
        {
            System.err.println("ERROR: No DNS record for '" + args[0] + "'");
        }
    }
}
