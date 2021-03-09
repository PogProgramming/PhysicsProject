using UnityEngine;

public class BulletAttack : MonoBehaviour
{
    private float bulletDamage = 0;
    private float bulletForce = 0;

    private Vector3 bulletDirection;

    Vector3 origin;

    Rigidbody rb;

    public void SetBullet(float damage, float speed, Vector3 direction)
    {
        bulletDamage = damage;
        bulletForce = speed;
        bulletDirection = direction;
    }

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        origin = transform.position;
        if (bulletDamage == 0 || bulletForce == 0) 
            Destroy(gameObject);

        rb.AddForce(bulletDirection * bulletForce, ForceMode.Force);
    }

    // Update is called once per frame
    void Update()
    {
        if (Vector3.Distance(origin, transform.position) > bulletForce) Destroy(gameObject);
    }

    void TargetHit()
    {
        Destroy(gameObject);
    }
}
