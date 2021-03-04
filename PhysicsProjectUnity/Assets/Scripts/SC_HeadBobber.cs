using UnityEngine;

public class SC_HeadBobber : MonoBehaviour
{
    public float walkingBobbingSpeed = 14f;
    public float bobbingAmount = 0.05f;
    public PlayerMovement controller;

    float defaultPosY = 0;
    float timer = 0;

    void Start()
    {
        defaultPosY = transform.localPosition.y;
    }

    void Update()
    {
        if (Mathf.Abs(controller.rb.velocity.x) > 0.1f || Mathf.Abs(controller.rb.velocity.z) > 0.1f)
        {
            if (controller.grounded) // Player is on the ground
            {
                //Player is moving
                timer += Time.deltaTime * walkingBobbingSpeed;
                transform.localPosition = new Vector3(transform.localPosition.x, defaultPosY + Mathf.Sin(timer) * bobbingAmount, transform.localPosition.z);
            }
        }
        else
        {
            //Idle
            timer = 0;
            transform.localPosition = new Vector3(transform.localPosition.x, Mathf.Lerp(transform.localPosition.y, defaultPosY, Time.deltaTime * walkingBobbingSpeed), transform.localPosition.z);
        }
    }
}