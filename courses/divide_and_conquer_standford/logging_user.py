import time
# This class handles logging in text file
class Logging:
	def __init__(self, log_path, log_status):
		self.log_path = log_path
		self.log_status = log_status
		self.log_off = True
		self.__configureLogFile()

	def writeLog(self, log_msg, log=False):
		if (self.log_off == True):
			if (self.log_status or log):
				with open(self.log_path, "a") as log:	
					log.write("\r" + time.ctime() + ": ")
					log.write(log_msg)

	# Create log file if it doesn't exist or clear if exists		
	def __configureLogFile(self):
			open(self.log_path, "w+").close()

	def logOff(self):
		self.log_off = False

