from twilio.rest import Client

# Twilio Credentials
ACCOUNT_SID = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
AUTH_TOKEN = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
TWILIO_WHATSAPP_NUMBER = "whatsapp:+141XXXXXXX"  # Twilio Sandbox Number
USER_WHATSAPP_NUMBER = "whatsapp:+977XXXXXXXXXX"  # User's WhatsApp number

def send_whatsapp_alert(account_number):
    try:
        client = Client(ACCOUNT_SID, AUTH_TOKEN)
        message = client.messages.create(
            from_=TWILIO_WHATSAPP_NUMBER,
            body=f"Alert! Multiple failed login attempts on your ATM account: {account_number}. If this wasn't you, contact support immediately.",
            to=USER_WHATSAPP_NUMBER
        )
        print(f"WhatsApp alert sent successfully! Message SID: {message.sid}")
    except Exception as e:
        print(f"Error sending WhatsApp alert: {e}")
