using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Raycast : MonoBehaviour
{
    public Text output;
    void Start()
    {
        
    }

    void Update()
    {
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        RaycastHit hitInfo;
        if (Physics.Raycast(ray, out hitInfo, 500) == true)
        {
            if (!output.enabled) output.enabled = true;
            output.text = hitInfo.transform.gameObject.name;
        }
        else if (output.enabled) output.enabled = false;
    }
}
