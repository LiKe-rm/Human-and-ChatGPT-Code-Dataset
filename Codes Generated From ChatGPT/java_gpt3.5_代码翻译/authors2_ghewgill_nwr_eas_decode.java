import java.util.*;
import java.util.regex.*;

public class EASDecode {
    static class Description {
        String abbr;
        String desc;

        Description(String abbr, String desc) {
            this.abbr = abbr;
            this.desc = desc;
        }
    }

    static class County {
        int fips;
        String name;

        County(int fips, String name) {
            this.fips = fips;
            this.name = name;
        }
    }

    static class Message {
        String raw;
        String originator;
        String originator_desc;
        String event;
        String event_desc;
        List<Area> areas;
        long issued;
        long received;
        long purge;
        String sender;
        String sender_desc;

        static class Area {
            String code;
            int part;
            int state;
            int county;
            String desc;
        }
    }

    // 使用静态变量存储描述符和县
    private static final List<Description> Originators = Arrays.asList(
        new Description("CIV", "Civil authorities"),
        new Description("EAS", "Broadcast station or cable station"),
        new Description("PEP", "Primary Entry Point System"),
        new Description("WXR", "National Weather Service")
    );

    private static final List<Description> Events = Arrays.asList(
        // 省略一部分事件描述以节省空间
        new Description("ADR", "Administrative Message"),
        new Description("AVA", "Avalanche Watch"),
        new Description("AVW", "Avalanche Warning")
    );

    private static final List<County> Counties = Arrays.asList(
        // 省略一部分县数据以节省空间
        new County(1001, "Autauga"),
        new County(1003, "Baldwin")
    );

    private static final String[] Parts = {
        "",
        "Northwest ",
        "North ",
        "Northeast ",
        "West ",
        "Central ",
        "East ",
        "Southwest ",
        "South ",
        "Southeast ",
    };

    private static String getOriginatorDesc(String originator) {
        return Originators.stream()
                .filter(d -> d.abbr.equals(originator))
                .map(d -> d.desc)
                .findFirst()
                .orElse("");
    }

    private static String getEventDesc(String event) {
        return Events.stream()
                .filter(d -> d.abbr.equals(event))
                .map(d -> d.desc)
                .findFirst()
                .orElse("");
    }

    private static String getAreaDesc(Message.Area area) {
        int fips = 1000 * area.state + area.county;
        County county = Counties.stream()
                .filter(c -> c.fips == fips)
                .findFirst()
                .orElse(null);
        if (county == null) {
            return "";
        }
        return Parts[area.part] + county.name;
    }

    private static String getSenderDesc(String sender) {
        return "";
    }

    public static boolean decode(String s, Message message) {
        Pattern pattern = Pattern.compile("^ZCZC-(\\w+)-(\\w+)((?:-[^+-]+){1,31})\\+(\\d{2})(\\d{2})-(\\d{3})(\\d{2})(\\d{2})-([^-]+)-");
        Matcher matcher = pattern.matcher(s);

        if (!matcher.find()) {
            return false;
        }

        int yday = Integer.parseInt(matcher.group(6));
        ZonedDateTime now = ZonedDateTime.now(ZoneOffset.UTC);
        while (true) {
            int currentYday = now.getDayOfYear();
            if (currentYday == yday) {
                break;
            } else if (currentYday < yday) {
                now = now.plusDays(1);
            } else {
                now = now.minusDays(1);
            }
        }
    
        message.raw = s;
        message.originator = matcher.group(1);
        message.originator_desc = getOriginatorDesc(message.originator);
        message.event = matcher.group(2);
        message.event_desc = getEventDesc(message.event);
        message.areas = new ArrayList<>();
    
        String[] areaCodes = matcher.group(3).substring(1).split("-");
        for (String areaCode : areaCodes) {
            Message.Area area = new Message.Area();
            area.code = areaCode;
            if (areaCode.length() == 6 && areaCode.chars().allMatch(Character::isDigit)) {
                area.part = Character.digit(areaCode.charAt(0), 10);
                area.state = 10 * Character.digit(areaCode.charAt(1), 10) + Character.digit(areaCode.charAt(2), 10);
                area.county = 100 * Character.digit(areaCode.charAt(3), 10) + 10 * Character.digit(areaCode.charAt(4), 10) + Character.digit(areaCode.charAt(5), 10);
            }
            area.desc = getAreaDesc(area);
            message.areas.add(area);
        }
    
        message.issued = now.withHour(Integer.parseInt(matcher.group(7)))
                .withMinute(Integer.parseInt(matcher.group(8)))
                .withSecond(0)
                .toInstant()
                .toEpochMilli();
        message.received = Instant.now().toEpochMilli();
        message.purge = message.issued + 60 * (60 * Integer.parseInt(matcher.group(4)) + Integer.parseInt(matcher.group(5)));
        message.sender = matcher.group(9);
        message.sender_desc = getSenderDesc(message.sender);
    
        return true;
    }
    
    public static void main(String[] args) {
        String input = "ZCZC-WXR-TOR-012345-0200-2122212-0500+0015-NOAA-";
        Message message = new Message();
        if (decode(input, message)) {
            System.out.println("Message decoded successfully.");
            System.out.println("Originator: " + message.originator);
            System.out.println("Originator description: " + message.originator_desc);
            System.out.println("Event: " + message.event);
            System.out.println("Event description: " + message.event_desc);
            System.out.println("Areas: ");
            for (Message.Area area : message.areas) {
                System.out.println("  Code: " + area.code);
                System.out.println("  Description: " + area.desc);
            }
            System.out.println("Issued: " + Instant.ofEpochMilli(message.issued));
            System.out.println("Purge: " + Instant.ofEpochMilli(message.purge));
            System.out.println("Sender: " + message.sender);
        } else {
            System.out.println("Failed to decode the message.");
        }
    }
    
}
