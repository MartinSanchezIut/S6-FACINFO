from selenium import webdriver
from selenium.webdriver.firefox.firefox_binary import FirefoxBinary
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities

if __name__ == "__main__":
    d = DesiredCapabilities.FIREFOX
    binary = FirefoxBinary(r"C:\Program Files\Firefox Developer Edition\firefox.exe")
    driver = webdriver.Firefox(firefox_binary=binary, capabilities=d)
    extension_path = 'F:\TER\enhanced_web_page_adaptation-2.1.4-an+fx.xpi'  # Must be the full path to an XPI file!
    driver.install_addon(extension_path, temporary=True)
    driver.get("https://stackoverflow.com/")

    for entry in driver.get_log('browser'):
        print(entry)
