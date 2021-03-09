using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovingPlatform : MonoBehaviour
{

    GameObject colSearchObj;
    public float colSearchRadius = 20f;
    public LayerMask affectedLayerMask;

    bool atStart = true;

    public float speed;
    public Vector3 startPos;
    public Vector3 endPos;

    bool movingElevator = false;

    Collider[] moveableObjects;

    void Start()
    {
        colSearchObj = GetComponentsInChildren<Transform>()[0].gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.K))
        {
            if (!movingElevator)
            {
                movingElevator = true;

                moveableObjects = Physics.OverlapSphere(colSearchObj.transform.position, colSearchRadius, affectedLayerMask);
                foreach (Collider col in moveableObjects)
                {
                    col.transform.SetParent(transform);
                }
            }
        }
    }

    void FixedUpdate()
    {
        if (movingElevator)
        {
            if (atStart)
            {
                transform.position = Vector3.Lerp(transform.position, endPos, speed * Time.fixedDeltaTime);

                if (Vector3.Distance(transform.position, endPos) < 0.05f)
                {
                    movingElevator = false;
                    atStart = false;

                    foreach (Collider col in moveableObjects)
                        col.transform.SetParent(null);

                    transform.position = endPos;
                }
            }
            else
            {
                transform.position = Vector3.Lerp(transform.position, startPos, speed * Time.fixedDeltaTime);

                if (Vector3.Distance(transform.position, startPos) < 0.05f)
                {
                    movingElevator = false;
                    atStart = true;

                    foreach (Collider col in moveableObjects)
                        col.transform.SetParent(null);

                    transform.position = startPos;
                }
            }

        }
    }
}

// start
// -3, 1, 19

// end
// -10.25, 14.125, 6