import time
import requests
import json
import random

from selenium import webdriver
from selenium.webdriver.common.keys import Keys


class testDevice:
  def __init__(self,deviceId, deviceKey):
    self.id = deviceId
    self.key = deviceKey

def create_webdriver(testdeviceid):
    ###log in MCS web############################################################
    options = webdriver.ChromeOptions()
    options.add_argument('--ignore-certificate-errors')
    options.add_argument("--test-type")
    driver = webdriver.Chrome("./chromedriver")
    driver.get('https://m...content-available-to-author-only...k.com/oauth/en/login')

    elem_user = driver.find_element_by_name("email")
    elem_user.send_keys("b08901039@ntu.edu.tw")
    elem_pwd = driver.find_element_by_name("password")
    elem_pwd.send_keys("f1127EE1688")
    elem_pwd.send_keys(Keys.RETURN)
    time.sleep(2)
    # click submit button
    submit_button = \
    driver.find_elements_by_xpath("//a[@href='./development/products/PxBh5sJC4sSI' and @class='ng-binding']")[0]
    submit_button.click()
    time.sleep(2)

    Development_button = driver.find_element_by_xpath("//i[@class='fa fa-wrench']")
    Development_button.click()
    time.sleep(2)

    Test_devices = driver.find_elements_by_xpath("//a[@href='/v2console/testdevices']")[0]
    Test_devices.click()
    time.sleep(2)


    if testdeviceid == "for_iLight":
        iLight_testdevice_detail_btn = driver.find_elements_by_xpath("//a[@id='button-devices-detail']")[0]
        iLight_testdevice_detail_btn.click()
        time.sleep(2)

    elif testdeviceid == "for_iLock":
        iLock_testdevice_detail_btn = driver.find_elements_by_xpath("//a[@id='button-devices-detail']")[1]
        iLock_testdevice_detail_btn.click()
        time.sleep(2)
    elif testdeviceid == "for_iGlove":
        iGlove_testdevice_detail_btn = driver.find_elements_by_xpath("//a[@id='button-devices-detail']")[2]
        iGlove_testdevice_detail_btn.click()
        time.sleep(2)

    return driver

    #########################################################################################



def get_value(testDevice,datachannelId):
    print("exectue: get_value()")

    host = "http://a...content-available-to-author-only...k.com"
    endpoint = "/mcs/v2/devices/" + testDevice.id+"/datachannels/"+datachannelId+"/datapoints"###Humidity是datachannel
    url = host + endpoint
    headers = {"content-type":"text", "deviceKey": testDevice.key}
    r = requests.get(url, headers=headers)

    s1=json.loads(r.text)
    print("     s1:",s1)
    value=s1['dataChannels'][0]['dataPoints'][0]['values']['value']
    #print(value)
    print("")
    return value

def post_value(testDevice,payload):
  print("execute: post_value")

  host = "http://a...content-available-to-author-only...k.com"
  endpoint = "/mcs/v2/devices/" + testDevice.id + "/datapoints"
  # url = ''.join([host,endpoint])
  url = host + endpoint

  headers = {"Content-type": "application/json", "deviceKey": testDevice.key}
  r = requests.post(url,headers=headers,data=json.dumps(payload))
  print('      from post_value,payload: ',payload)
  print("")
  #print('from_post_to_mcs,r.text: ',r.text)
  #print('from post_value,r.url: ',r.url)

def create_datapoint(dataChannelId,value):
    ### payload={"datapoints":[create_datapoint,create_datapoint,create_datapoint,...]}
    return {"dataChnId": dataChannelId, "values": {"value":value }}
    ### payload = {"datapoints": [{"dataChnId": "Humidity", "values": {"value": h0}},
        ###                   {"dataChnId": "Temperature", "values": {"value": t0}}]}

def create_payload(datapoint_list):
    ##datapoint_list be like: [create_datapoiint(),create_darapoint,...]
    return{"datapoints":datapoint_list}



######################test_device:python _test_testDevice#####
deviceId = "DKOAIjdm"
deviceKey = "m3M1BWajznxsNdrP"

######################test_device:led_test_testDevice###########
deviceId2='DsmD3HYe'
deviceKey2='hguTF5a0ANsTSz0E'

######################################################################

python_testDevice=testDevice("DKOAIjdm","m3M1BWajznxsNdrP")

ledtest_testDevice=testDevice('DsmD3HYe','hguTF5a0ANsTSz0E')


iLight_testDevice=testDevice('D9e4h3ov','pT0Yz4XDXUx54WiJ')
##Channid:{for_iLight: string}

iLock_testDevice=testDevice('DuEA00oC','AgAxdaJmywe1HKTG')
##Channid:{for_iLock: string}

iGlove_testDevice=testDevice('DwHgZZlg','qPJZlPGOOXeK3Xxc')
##Channid:{to_iLight: string, to_iLock:String}


def execute_python_test():
    h0 = random.randint(0, 30)
    t0 = random.randint(0, 30)
    datapoint_python_testDevice_Humidity = create_datapoint("Humidity", h0)
    datapoint_python_testDevice_Temperature = create_datapoint("Temperature", t0)
    payload_python_testDevice = create_payload(
        [datapoint_python_testDevice_Humidity, datapoint_python_testDevice_Temperature])
    post_value(python_testDevice, payload_python_testDevice)

    print("")
    get_value(python_testDevice, "Humidity")
    get_value(python_testDevice, "Temperature")

def execute_for_iLight_test(driver_iLight,value_of_to_iLight):

    t0 = str(random.randint(0, 30))

    datapoint_iLight_for_iLight = create_datapoint("for_iLight", value_of_to_iLight)##t0換成value_of_to_iLight
    payload_iLight = create_payload([datapoint_iLight_for_iLight])
    post_value(iLight_testDevice,payload_iLight)

    print("")
    get_value(iLight_testDevice, "for_iLight")

    ok_click_button=driver_iLight.find_elements_by_xpath("//a[@class='btn btn-info ng-binding']")[0]
    ok_click_button.click()


def execute_for_iLock_test(driver_iLock,value_of_to_iLock):

    #t0 = str(random.randint(0, 30))

    datapoint_iLock_for_iLock = create_datapoint("for_iLock", value_of_to_iLock)##t0換成value_of_for_iLock
    payload_iLock = create_payload([datapoint_iLock_for_iLock])
    post_value(iLock_testDevice,payload_iLock)

    print("")
    get_value(iLock_testDevice, "for_iLock")

    ok_click_button=driver_iLock.find_elements_by_xpath("//a[@class='btn btn-info ng-binding']")[1]
    ok_click_button.click()
def post_value_to_iGlove(value_of_to_iLock,value_of_to_iLight):
    print('execute: post_value_to_iGlove()')
    datapoint_iGlove_to_iLock = create_datapoint("to_iLock", value_of_to_iLock)
    datapoint_iGlove_to_iLight = create_datapoint("to_iLight", value_of_to_iLight)

    payload_iGlove = create_payload([datapoint_iGlove_to_iLock,datapoint_iGlove_to_iLight])
    post_value(iGlove_testDevice,payload_iGlove)

    print("")
    #get_value(iGlove_testDevice, "for_iLock")



driver_iLight=create_webdriver("for_iLight")
driver_iLock=create_webdriver("for_iLock")
driver_iGlove=create_webdriver("for_iGlove")


post_value_to_iGlove('','')
print("end initial setting #################################################")

while True:
  #light=str(random.randint(0,30))
  #lock = str(random.randint(60, 90))
  #post_value_to_iGlove(lock,light)




  print('get_value(iGlove_testDevice,"to_iLock")')
  value_of_to_iLock=get_value(iGlove_testDevice,"to_iLock")
  print("")

  print('get_value(iGlove_testDevice,"to_iLight")')
  value_of_to_iLight=get_value(iGlove_testDevice,"to_iLight")
  print("")


  print('execute####################################################')
  execute_for_iLock_test(driver_iLock,value_of_to_iLock)
  execute_for_iLight_test(driver_iLight,value_of_to_iLight)





  ################################################################################

  print("one turn end ##################################################")

  time.sleep(0.1)

