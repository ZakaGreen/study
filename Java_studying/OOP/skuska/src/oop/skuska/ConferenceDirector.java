package oop.skuska;

public class ConferenceDirector {
    private EmailBuilderInterface builder;
    private String sender;
    private String senderName;
    private String recipient;
    private String recipientName;
    private String conferenceName;
    private String conferenceLocation;
    private String conferenceDate;
    private String conferenceTime;

    public ConferenceDirector(EmailBuilderInterface builder, String sender, String senderName) {
        this.builder = builder;
        this.sender = sender;
        this.senderName = senderName;
    }

    public void invite(String recipient, String recipientName, String conferenceName, String conferenceLocation, String conferenceDate, String conferenceTime) {
        builder.reset();
        this.recipient = recipient;
        this.recipientName = recipientName;
        this.conferenceName = conferenceName;
        this.conferenceLocation = conferenceLocation;
        this.conferenceDate = conferenceDate;
        this.conferenceTime = conferenceTime;

        builder.setSender(sender);
        builder.setReceiver(recipient);
        builder.setSubject(String.format("%s (invitation)", conferenceName));
        builder.setContent(String.format("""
                Dear %s,
                We are pleased to invite you to our upcoming conference, %s.
                The conference is scheduled to take place on %s, at %s, in %s.
                Sincerely,
                %s
                """, recipientName, conferenceName, conferenceDate, conferenceTime, conferenceLocation, senderName));
    }

    public void confirm(String recipient, String recipientName, String conferenceName) {
        builder.reset();
        this.recipient = recipient;
        this.recipientName = recipientName;
        this.conferenceName = conferenceName;

        builder.setSender(sender);
        builder.setReceiver(recipient);
        builder.setSubject(String.format("%s (registration confirmation)", conferenceName));
        builder.setContent(String.format("""
                Dear %s,
                We are delighted to confirm your registration for the %s conference.
                Sincerely,
                %s
                """, recipientName, conferenceName, senderName));
    }



    // v komentaroch su popisane
    //  - parametre konstruktora a metod
    //  - texty, aby ste ich nemuseli prepisovat rucne (pre zostavenie mozete pouzit funkciu String.format)

    // constructor(builder, adresa odosielatela, meno odosielatela) {
    // }


    // pozvanka na konferenciu
    // void invite(adresa prijimatela, meno prijimatela, nazov konferencie, miesto konania, datum konania, cas konania) {

        // predmet spravy
        // "%s (invitation)"

        // obsah emailu
        // """
        // Dear %s,
        // We are pleased to invite you to our upcoming conference, %s.
        // The conference is scheduled to take place on %s, at %s, in %s.
        // Sincerely,
        // %s
        //     """

    // }

    // potvrdenie rezervacie
    // void confirm(adresa prijimatela, meno prijimatela, nazov konferencie) {

        // predmet spravy
        // "%s (registration confirmation)"

        // obsah emailu
        // """
        // Dear %s,
        // We are delighted to confirm your registration for the %s conference.
        // Singecerly,
        // %s
        // """

    // }
}
