import json
import boto3

dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table('smart_dispenser_data')

def lambda_handler(event, context):
    try:
        data_item  =  {
            'thing_name' : event.get('thing_name'),
            'timestamp' : event.get('timestamp'),
            'weight': event.get('weight')
        }
        response = table.put_item(Item=data_item)
        return {
            'statusCode': 200,
        }
    except Exception as e:
        print(f"Exception: {e}")
