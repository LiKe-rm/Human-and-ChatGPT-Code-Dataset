class CKIRCProtocolListener {
public:
	CKIRCProtocolListener(CKIRCProtocol* aProtocol);
	CKIRCProtocolListener(const CKIRCProtocolListener& aListener);
	~CKIRCProtocolListener();
	CKIRCProtocolListener& operator=(const CKIRCProtocolListener& aListener);
	bool operator==(const CKIRCProtocolListener& aListener) const;
	bool operator!=(const CKIRCProtocolListener& aListener) const;
	std::string toString() const;
	void setTimeToDie(bool aFlag);
	bool timeToDie() const;
	void setIsRunning(bool aFlag);
	bool isRunning() const;
	CKIRCProtocol* getProtocol() const;
	void process();
private:
	CKIRCProtocol* mProtocol;
	bool mTimeToDie;
	bool mIsRunning;
	void parseMessage(const std::string& aMessage);
	void handleUserMessage(const std::string& aMessage);
};

CKIRCProtocolListener::CKIRCProtocolListener(CKIRCProtocol* aProtocol) :
	mProtocol(aProtocol),
	mTimeToDie(false),
	mIsRunning(false)
{
}

CKIRCProtocolListener::CKIRCProtocolListener(const CKIRCProtocolListener& aListener) :
	mProtocol(aListener.mProtocol),
	mTimeToDie(aListener.mTimeToDie),
	mIsRunning(aListener.mIsRunning)
{
}

CKIRCProtocolListener::~CKIRCProtocolListener()
{
}

CKIRCProtocolListener& CKIRCProtocolListener::operator=(const CKIRCProtocolListener& aListener)
{
	if (this != &aListener)
	{
		mProtocol = aListener.mProtocol;
		mTimeToDie = aListener.mTimeToDie;
		mIsRunning = aListener.mIsRunning;
	}
	return *this;
}

bool CKIRCProtocolListener::operator==(const CKIRCProtocolListener& aListener) const
{
	return (mProtocol == aListener.mProtocol &&
		mTimeToDie == aListener.mTimeToDie &&
		mIsRunning == aListener.mIsRunning);
}

bool CKIRCProtocolListener::operator!=(const CKIRCProtocolListener& aListener) const
{
	return !(*this == aListener);
}

std::string CKIRCProtocolListener::toString() const
{
	std::stringstream ss;
	ss << "CKIRCProtocolListener("
		<< "protocol=" << mProtocol
		<< ", timeToDie=" << mTimeToDie
		<< ", isRunning=" << mIsRunning
		<< ")";
	return ss.str();
}

void CKIRCProtocolListener::setTimeToDie(bool aFlag)
{
	mTimeToDie = aFlag;
}

bool CKIRCProtocolListener::timeToDie() const
{
	return mTimeToDie;
}

void CKIRCProtocolListener::setIsRunning(bool aFlag)
{
	mIsRunning = aFlag;
}

bool CKIRCProtocolListener::isRunning() const
{
	return mIsRunning;
}

CKIRCProtocol* CKIRCProtocolListener::getProtocol() const
{
	return mProtocol;
}

void CKIRCProtocolListener::process()
{
	while (!timeToDie())
	{
		if (mProtocol && mProtocol->isConnected())
		{
			std::string message = mProtocol->getMessage();
			if (!message.empty())
			{
				parseMessage(message);
			}
		}
		// Wait for a short time before checking for new messages again
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	setIsRunning(false);
}

void CKIRCProtocolListener::parseMessage(const std::string& a
	{
		// Parse the message and forward it to the chat user if it's a user message
		if (aMessage.find("PRIVMSG") != std::string::npos)
		{
		handleUserMessage(aMessage);
		}
	}

	void CKIRCProtocolListener::handleUserMessage(const std::string& aMessage)
	{
		// Extract the username and message text from the PRIVMSG command
		std::size_t pos = aMessage.find("!");
		std::string username = aMessage.substr(1, pos - 1);
		pos = aMessage.find(":", pos);
		std::string message = aMessage.substr(pos + 1);
		// Send the message to the chat user
		// Here we assume that there is a global variable "chatUser" representing the chat user object
		chatUser.receiveMessage(username, message);
	}