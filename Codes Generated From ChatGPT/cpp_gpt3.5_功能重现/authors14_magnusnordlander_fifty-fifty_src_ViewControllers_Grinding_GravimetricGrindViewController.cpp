#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "Settings.h"
#include "ScaleWrapper.h"

class GravimetricGrindViewController {
public:
	GravimetricGrindViewController(Settings& settings, ScaleWrapper& scaleWrapper)
		: m_settings(settings)
		, m_scaleWrapper(scaleWrapper)
		, m_state(IDLE)
		, m_startTime(0)
		, m_stopTime(0)
		, m_grindWeight(0)
		, m_totalWeight(0)
		, m_grinderOn(false)
		, m_relayPin(13)
	{}

	void begin() {
		pinMode(m_relayPin, OUTPUT);
		digitalWrite(m_relayPin, LOW);
	}

	void tick() {
		switch (m_state) {
		case IDLE:
			if (shouldStartGrind()) {
				startGrind();
			}
			break;
		case GRINDING:
			if (shouldStopGrind()) {
				stopGrind();
			}
			else {
				updateGrindWeight();
			}
			break;
		case STOPPED:
			if (shouldRestartGrind()) {
				restartGrind();
			}
			break;
		default:
			break;
		}
	}

	void render() {
		switch (m_state) {
		case IDLE:
			Serial.println("Idle");
			break;
		case GRINDING:
			Serial.print("Grinding ");
			Serial.print(m_grindWeight);
			Serial.print(" / ");
			Serial.println(m_settings.getTargetWeight());
			break;
		case STOPPED:
			Serial.print("Stopped ");
			Serial.print(m_totalWeight);
			Serial.print(" / ");
			Serial.println(m_settings.getTargetWeight());
			break;
		default:
			break;
		}
	}

private:
	enum State {
		IDLE,
		GRINDING,
		STOPPED,
	};

	Settings& m_settings;
	ScaleWrapper& m_scaleWrapper;
	State m_state;
	unsigned long m_startTime;
	unsigned long m_stopTime;
	float m_grindWeight;
	float m_totalWeight;
	bool m_grinderOn;
	int m_relayPin;

	bool shouldStartGrind() {
		float weight = m_scaleWrapper.getWeight();
		if (weight > 0 && weight < m_settings.getTargetWeight()) {
			return true;
		}
		return false;
	}

	bool shouldStopGrind() {
		float weight = m_scaleWrapper.getWeight();
		if (weight >= m_settings.getTargetWeight()) {
			return true;
		}
		return false;
	}

	bool shouldRestartGrind() {
		float weight = m_scaleWrapper.getWeight();
		if (weight < m_settings.getTargetWeight() / 2) {
			return true;
		}
		return false;
	}

	void startGrind() {
		m_grindWeight = 0;
		m_totalWeight = 0;
		m_grinderOn = true;
		m_startTime = millis();
		m_state = GRINDING;
		digitalWrite(m_relayPin, HIGH);
	}

	void stopGrind() {
		m_grinderOn = false;
		m_stopTime = millis();
		m_totalWeight += m_grindWeight;
		m_state = STOPPED;
		digitalWrite(m_relayPin, LOW);
	}

	void restartGrind() {
		m_grindWeight = 0;
		m_grinderOn = true;
		m_startTime = millis();
		m_state = GRINDING;
		digitalWrite(m_relayPin, HIGH);
	}

	void updateGrindWeight() {
		float weight = m_scaleWrapper.getWeight();
		m_grindWeight = weight - m_totalWeight;
	}
};

int main() {
	Settings settings;
	ScaleWrapper scaleWrapper;
	GravimetricGrindViewController controller(settings, scaleWrapper);

	controller.begin();

	while (true) {
		controller.tick();
		controller.render();
		_delay_ms(100);
	}

	return 0;
}
